﻿#region License
/* 
 * Copyright (C) 1999-2017 John Källén.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 */
#endregion

using Reko.Core.Expressions;
using Reko.Core.Rtl;
using Reko.Core.Types;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Reko.Arch.Vax
{
    public partial class VaxRewriter
    {
        private void RewriteBicpsw()
        {
            var mask = RewriteSrcOp(0, PrimitiveType.UInt16);
            var psw = frame.EnsureRegister(Registers.psw);
            m.Assign(psw, m.And(psw, m.Comp(mask)));
        }

        private void RewriteBispsw()
        {
            var mask = RewriteSrcOp(0, PrimitiveType.UInt16);
            var psw = frame.EnsureRegister(Registers.psw);
            m.Assign(psw, m.Or(psw, mask));
        }

        private void RewriteHalt()
        {
            rtlc = RtlClass.Terminates;
            m.SideEffect(host.PseudoProcedure("__halt", VoidType.Instance));
        }

        private void RewriteInsque()
        {
            var entry = RewriteSrcOp(0, PrimitiveType.Word32);
            var queue = RewriteSrcOp(1, PrimitiveType.Word32);
            var grf = FlagGroup(FlagM.NZC);
            m.Assign(grf, host.PseudoProcedure("__insque", grf.DataType, queue, entry));
            m.Assign(FlagGroup(FlagM.VF), Constant.False());
        }

        private void RewriteBpt()
        {
            m.SideEffect(host.PseudoProcedure("vax_bpt", VoidType.Instance));
        }

        private void RewriteChme()
        {
            m.SideEffect(host.PseudoProcedure("vax_chme", VoidType.Instance,
                RewriteSrcOp(0, PrimitiveType.Word16)));
        }
    }
}
