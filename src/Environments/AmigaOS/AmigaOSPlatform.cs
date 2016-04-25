﻿#region License
/* 
 * Copyright (C) 1999-2016 John Källén.
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

using Reko.Arch.M68k;
using Reko.Core;
using Reko.Core.Expressions;
using Reko.Core.Lib;
using Reko.Core.Operators;
using Reko.Core.Rtl;
using Reko.Core.Serialization;
using Reko.Core.Services;
using Reko.Core.Types;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.IO;
using System.Linq;
using System.Text;
using Reko.Core.CLanguage;

namespace Reko.Environments.AmigaOS
{
    /// <summary>
    /// Represents the AmigaOS platform.
    /// </summary>
    [Designer("Reko.Environments.AmigaOS.Design.AmigaOSPlatformDesigner,Reko.Environments.AmigaOS.Design")]
    public class AmigaOSPlatform : Platform
    {
        private RtlInstructionMatcher a6Pattern;
        private Dictionary<int, SystemService> funcs; //$TODO: This should take a type of base pointer the reference is from ?
        private static Dictionary<int, List<String>> mapKickstartToListOfLibraries = new Dictionary<int, List<String>>
        {
            {
                33, new List<String>
                {
                    "exec_v33",
                    "dos_v33"
                }
            },
            {
                34, new List<String>
                {
                    "exec_v34",
                    "dos_v34"
                }
            }
        }; //$TODO: Load available kickstart -> libraries mappings from disk ?

        public AmigaOSPlatform(IServiceProvider services, IProcessorArchitecture arch)
            : base(services, arch, "amigaOS")
        {
            this.a6Pattern = new RtlInstructionMatcher(
                new RtlCall(
                    new BinaryExpression(
                        Operator.IAdd,
                        PrimitiveType.Word32,
                        ExpressionMatcher.AnyId("addrReg"),
                        ExpressionMatcher.AnyConstant("offset")),
                    4,
                    RtlClass.Transfer));
        }

        public static Dictionary<int, List<String>> MapKickstartToListOfLibraries
        {
            get
            {
                return mapKickstartToListOfLibraries;
            }
        }

        public override ProcedureSerializer CreateProcedureSerializer(ISerializedTypeVisitor<DataType> typeLoader, string defaultConvention)
        {
            throw new NotImplementedException();
        }

        public override HashSet<RegisterStorage> CreateImplicitArgumentRegisters()
        {
            return new HashSet<RegisterStorage> { Registers.a7 };
        }

        public override SystemService FindService(int vector, ProcessorState state)
        {
            return null;
        }

        public override SystemService FindService(RtlInstruction rtl, ProcessorState state)
        {
            EnsureTypeLibraries(PlatformIdentifier);
            if (!a6Pattern.Match(rtl))
                return null;
            var reg = ((Identifier) a6Pattern.CapturedExpressions("addrReg")).Storage as RegisterStorage;
            var offset = ((Constant) a6Pattern.CapturedExpressions("offset")).ToInt32();
            if (reg != Registers.a6)
                return null;
            if (funcs == null)
                funcs = LoadLibraryDef("exec", 33, Metadata);
            SystemService svc;
            return funcs.TryGetValue(offset, out svc) ? svc : null;
        }

        private String GetLibraryBaseName(String name_with_version) 
        {
            int idx_of_version_str = name_with_version.IndexOf("_v");
            if (-1 == idx_of_version_str) // no version, assuming the base name of library is same as name_with_version
                return name_with_version;
            return name_with_version.Substring(0, idx_of_version_str);
        }

        /// <summary>
        /// Gets the list of libraries for given kickstart version.
        /// </summary>
        /// <returns>The library list for kickstart version.</returns>
        /// <remarks> This will always try to build maximum list of libraries, using older versions where possible </remarks>
        /// <param name="ver">Kickstart version</param>
        public List<string> GetLibrarySetForKickstartVersion(int ver)
        {
            //$TODO: needs cleanup ?
            var result_list = new List<String>();
            var selected_librarties = new Dictionary<String,String>();

            var keys = mapKickstartToListOfLibraries.Keys.ToList();
            keys.Sort();

            int idx_version_to_select = keys.BinarySearch(ver);
            if (idx_version_to_select<0) 
            {
                int next_larger_idx = ~idx_version_to_select;
                // if ver > highest available - use highest available
                if (next_larger_idx == keys.Count)
                    idx_version_to_select =  keys.Count - 1;
                // if ver < lowest available - return empty list
                else if (next_larger_idx == 0)
                    return result_list;
            }
            for (int ver_idx = idx_version_to_select; ver_idx >= 0; --ver_idx) 
            {
                int try_version = keys.ElementAt(ver_idx);
                foreach (string lib in mapKickstartToListOfLibraries[try_version]) 
                {
                    string base_libname = GetLibraryBaseName(lib);
                    if (selected_librarties.ContainsKey(base_libname))
                        continue;
                    selected_librarties.Add(base_libname, lib);
                }
            }
            return selected_librarties.Values.ToList();
        }
        public void SetKickstartVersion(int v)
        {
            List<String> lib_list = GetLibrarySetForKickstartVersion (v);

        }
        public override string DefaultCallingConvention
        {
            get { return ""; }
        }

        public override int GetByteSizeFromCBasicType(CBasicType cb)
        {
            switch (cb)
            {
            case CBasicType.Char: return 1;
            case CBasicType.WChar_t: return 2;  //$REVIEW: Does AmigaOS support wchar_t?
            case CBasicType.Short: return 2;
            case CBasicType.Int: return 4;
            case CBasicType.Long: return 4;
            case CBasicType.LongLong: return 8;
            case CBasicType.Float: return 4;
            case CBasicType.Double: return 8;
            case CBasicType.LongDouble: return 8;
            case CBasicType.Int64: return 8;
            default: throw new NotImplementedException(string.Format("C basic type {0} not supported.", cb));
            }
        }

        public override ProcedureBase GetTrampolineDestination(ImageReader imageReader, IRewriterHost host)
        {
            return null;
        }

        public override ExternalProcedure LookupProcedureByName(string moduleName, string procName)
        {
            throw new NotImplementedException();
        }

        public override Address MakeAddressFromConstant(Constant c)
        {
            return Address.Ptr32(c.ToUInt32());
        }

        private Dictionary<int, SystemService> LoadLibraryDef(string lib_name, int version, TypeLibrary libDst)
        {
            var tlSvc = Services.RequireService<ITypeLibraryLoaderService>();
            var fsSvc = Services.RequireService<IFileSystemService>();
            var sser = new M68kProcedureSerializer(
                (M68kArchitecture)Architecture,
                new TypeLibraryDeserializer(this, true, libDst),
                DefaultCallingConvention);

            using (var rdr = new StreamReader(fsSvc.CreateFileStream(tlSvc.InstalledFileLocation( lib_name + ".funcs"), FileMode.Open, FileAccess.Read)))
            {
                var fpp = new FuncsFileParser((M68kArchitecture)this.Architecture, rdr);
                fpp.Parse();
                return fpp.FunctionsByLibBaseOffset.Values
                    .Select(amiSvc => new SystemService
                    {
                        Name = amiSvc.Name,
                        SyscallInfo = new SyscallInfo
                        {
                            Vector = amiSvc.Offset,
                        },
                        Signature = sser.Deserialize(amiSvc.Signature, Architecture.CreateFrame()),   //$BUGBUG: catch dupes?   
                        Characteristics = new ProcedureCharacteristics { }
                    })
                    .ToDictionary(de => de.SyscallInfo.Vector, de => de);
            };
        }
    }
}
