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

using Reko.Core;
using Reko.Core.Types;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Reko.Arch.X86
{
    public class ThisCallConvention : CallingConvention
    {
        private RegisterStorage ecxThis;
        private int retAddressOnStack;
        private int stackAlignment;

        public ThisCallConvention(RegisterStorage ecxThis, int stackAlignment, int retAddressOnStack)
        {
            this.ecxThis = ecxThis;
            this.stackAlignment = stackAlignment;
            this.retAddressOnStack = retAddressOnStack;
        }

        public void Generate(ICallingConventionEmitter ccr, DataType dtRet, DataType dtThis, List<DataType> dtParams)
        {
            ccr.LowLevelDetails(stackAlignment, retAddressOnStack);
            X86CallingConvention.SetReturnStorage(ccr, dtRet, stackAlignment);

            for (int i = 0; i < dtParams.Count; ++i)
            {
                ccr.StackParam(dtParams[i]);
            }

            ccr.ImplicitThisRegister(this.ecxThis);

            ccr.CalleeCleanup();
        }
    }
}
