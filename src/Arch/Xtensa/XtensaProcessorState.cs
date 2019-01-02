﻿#region License
/* 
 * Copyright (C) 1999-2019 John Källén.
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

using System;
using Reko.Core;
using Reko.Core.Code;
using Reko.Core.Expressions;
using Reko.Core.Types;

namespace Reko.Arch.Xtensa
{
    public class XtensaProcessorState : ProcessorState
    {
        private XtensaArchitecture arch;
        private Address ip;

        public XtensaProcessorState(XtensaArchitecture arch)
        {
            this.arch = arch;
        }

        public XtensaProcessorState(XtensaProcessorState that) : base(that)
        {
            this.arch = that.arch;
            this.ip = that.ip;
        }

        public override IProcessorArchitecture Architecture {  get { return arch; } }

        public override ProcessorState Clone()
        {
            return new XtensaProcessorState(this);
        }

        public override Constant GetRegister(RegisterStorage r)
        {
            return Constant.Invalid;
        }

        public override void OnAfterCall(FunctionType sigCallee)
        {
        }

        public override CallSite OnBeforeCall(Identifier stackReg, int returnAddressSize)
        {
            return new CallSite(returnAddressSize, 0);
        }

        public override void OnProcedureEntered()
        {
        }

        public override void OnProcedureLeft(FunctionType procedureSignature)
        {
        }

        public override void SetInstructionPointer(Address addr)
        {
            this.ip = addr;
        }

        public override void SetRegister(RegisterStorage r, Constant v)
        {
        }
    }
}