//
// rsp/opcodes_priv.h: RSP opcode types and info.
//
// CEN64: Cycle-Accurate Nintendo 64 Simulator.
// Copyright (C) 2014, Tyler J. Stachecki.
//
// This file is subject to the terms and conditions defined in
// 'LICENSE', which is part of this source code package.
//

#ifndef __rsp_opcodes_priv_h__
#define __rsp_opcodes_priv_h__
#include "common.h"
#include "rsp/opcodes.h"

#define INFO1(x) (OPCODE_INFO_##x)
#define INFO2(x,y) (INFO1(x) | OPCODE_INFO_##y)
#define INFO3(x,y,z) (INFO2(x,y) | OPCODE_INFO_##z)
#define INFO4(x,y,z,a) (INFO3(x,y,z) | OPCODE_INFO_##a)
#define INFO5(x,y,z,a,b) (INFO4(x,y,z,a) | OPCODE_INFO_##b)
#define INVALID RSP_BUILD_OP(INVALID, INVALID, INFO1(NONE))
#define VINVALID RSP_BUILD_OP(VINVALID, VINVALID, INFO1(VECTOR))

#define ADDIU RSP_BUILD_OP(ADDIU, ADDIU_LUI_SUBIU, INFO1(NEEDRS))
#define ADDU RSP_BUILD_OP(ADDU, ADDU_SUBU, INFO2(NEEDRS, NEEDRT))
#define AND RSP_BUILD_OP(AND, AND_OR_XOR, INFO2(NEEDRS, NEEDRT))
#define ANDI RSP_BUILD_OP(ANDI, ANDI_ORI_XORI, INFO1(NEEDRS))
#define BEQ RSP_BUILD_OP(BEQ, BEQ_BNE, INFO3(BRANCH, NEEDRS, NEEDRT))
#define BGEZ RSP_BUILD_OP(BGEZ, BGEZ_BLTZ, INFO2(BRANCH, NEEDRS))
#define BGEZAL RSP_BUILD_OP(BGEZAL, BGEZAL_BLTZAL, INFO2(BRANCH, NEEDRS))
#define BGTZ RSP_BUILD_OP(BGTZ, BGTZ_BLEZ, INFO2(BRANCH, NEEDRS))
#define BLEZ RSP_BUILD_OP(BLEZ, BGTZ_BLEZ, INFO2(BRANCH, NEEDRS))
#define BLTZ RSP_BUILD_OP(BLTZ, BGEZ_BLTZ, INFO2(BRANCH, NEEDRS))
#define BLTZAL RSP_BUILD_OP(BLTZAL, BGEZAL_BLTZAL, INFO2(BRANCH, NEEDRS))
#define BNE RSP_BUILD_OP(BNE, BEQ_BNE, INFO3(BRANCH, NEEDRS, NEEDRT))
#define BREAK RSP_BUILD_OP(BREAK, BREAK, INFO1(NONE))
#define J RSP_BUILD_OP(J, J_JAL, INFO1(BRANCH))
#define JAL RSP_BUILD_OP(JAL, J_JAL, INFO1(BRANCH))
#define JALR RSP_BUILD_OP(JALR, JALR_JR, INFO2(BRANCH, NEEDRS))
#define JR RSP_BUILD_OP(JR, JALR_JR, INFO2(BRANCH, NEEDRS))
#define LB RSP_BUILD_OP(LB, LOAD, INFO2(NEEDRS, LOAD))
#define LBU RSP_BUILD_OP(LBU, LOAD, INFO2(NEEDRS, LOAD))
#define LH RSP_BUILD_OP(LH, LOAD, INFO2(NEEDRS, LOAD))
#define LHU RSP_BUILD_OP(LHU, LOAD, INFO2(NEEDRS, LOAD))
#define LUI RSP_BUILD_OP(LUI, ADDIU_LUI_SUBIU, INFO1(NONE))
#define LW RSP_BUILD_OP(LW, LOAD, INFO2(NEEDRS, LOAD))
#define NOP RSP_BUILD_OP(NOP, INVALID, INFO1(NONE))
#define NOR RSP_BUILD_OP(NOR, NOR, INFO2(NEEDRS, NEEDRT))
#define OR RSP_BUILD_OP(OR, AND_OR_XOR, INFO2(NEEDRS, NEEDRT))
#define ORI RSP_BUILD_OP(ORI, ANDI_ORI_XORI, INFO1(NEEDRS))
#define SB RSP_BUILD_OP(SB, STORE, INFO3(NEEDRS, NEEDRT, STORE))
#define SH RSP_BUILD_OP(SH, STORE, INFO3(NEEDRS, NEEDRT, STORE))
#define SLL RSP_BUILD_OP(SLL, SLL_SLLV, INFO1(NEEDRT))
#define SLLV RSP_BUILD_OP(SLLV, SLL_SLLV, INFO2(NEEDRS, NEEDRT))
#define SLT RSP_BUILD_OP(SLT, SLT, INFO2(NEEDRS, NEEDRT))
#define SLTI RSP_BUILD_OP(SLTI, SLTI, INFO1(NEEDRS))
#define SLTIU RSP_BUILD_OP(SLTIU, SLTIU, INFO1(NEEDRS))
#define SLTU RSP_BUILD_OP(SLTU, SLTU, INFO2(NEEDRS, NEEDRT))
#define SRA RSP_BUILD_OP(SRA, SRA, INFO1(NEEDRT))
#define SRAV RSP_BUILD_OP(SRAV, SRAV, INFO2(NEEDRS, NEEDRT))
#define SRL RSP_BUILD_OP(SRL, SRL, INFO1(NEEDRT))
#define SRLV RSP_BUILD_OP(SRLV, SRLV, INFO2(NEEDRS, NEEDRT))
#define SUBU RSP_BUILD_OP(SUBU, ADDU_SUBU, INFO1(NEEDRS))
#define SW RSP_BUILD_OP(SW, STORE, INFO3(NEEDRS, NEEDRT, STORE))
#define XOR RSP_BUILD_OP(XOR, AND_OR_XOR, INFO2(NEEDRS, NEEDRT))
#define XORI RSP_BUILD_OP(XORI, ANDI_ORI_XORI, INFO1(NEEDRS))

#define MFC0 RSP_BUILD_OP(MFC0, MFC0, INFO1(NONE))
#define MTC0 RSP_BUILD_OP(MTC0, MTC0, INFO1(NEEDRT))

#define CFC2 RSP_BUILD_OP(CFC2, CFC2, INFO1(NONE))
#define CTC2 RSP_BUILD_OP(CTC2, INVALID, INFO1(NONE))
#define MFC2 RSP_BUILD_OP(MFC2, INVALID, INFO1(NONE))
#define MTC2 RSP_BUILD_OP(MTC2, INVALID, INFO1(NONE))

#define VABS RSP_BUILD_OP(VABS, VABS, INFO3(VECTOR, NEEDVS, NEEDVT))
#define VADD RSP_BUILD_OP(VADD, VADD, INFO3(VECTOR, NEEDVS, NEEDVT))
#define VADDC RSP_BUILD_OP(VADDC, VADDC, INFO3(VECTOR, NEEDVS, NEEDVT))
#define VAND RSP_BUILD_OP(VAND, VAND, INFO3(VECTOR, NEEDVS, NEEDVT))
#define VCH RSP_BUILD_OP(VCH, VCH, INFO3(VECTOR, NEEDVS, NEEDVT))
#define VCL RSP_BUILD_OP(VCL, VCL, INFO3(VECTOR, NEEDVS, NEEDVT))
#define VCR RSP_BUILD_OP(VCR, VCR, INFO3(VECTOR, NEEDVS, NEEDVT))
#define VEQ RSP_BUILD_OP(VEQ, VEQ, INFO3(VECTOR, NEEDVS, NEEDVT))
#define VGE RSP_BUILD_OP(VGE, VGE, INFO3(VECTOR, NEEDVS, NEEDVT))
#define VLT RSP_BUILD_OP(VLT, VLT, INFO3(VECTOR, NEEDVS, NEEDVT))
#define VMACF RSP_BUILD_OP(VMACF, VINVALID, INFO1(VECTOR))
#define VMACQ RSP_BUILD_OP(VMACQ, VINVALID, INFO1(VECTOR))
#define VMACU RSP_BUILD_OP(VMACU, VINVALID, INFO1(VECTOR))
#define VMADH RSP_BUILD_OP(VMADH, VMADH, INFO3(VECTOR, NEEDVS, NEEDVT))
#define VMADL RSP_BUILD_OP(VMADL, VMADL, INFO3(VECTOR, NEEDVS, NEEDVT))
#define VMADM RSP_BUILD_OP(VMADM, VMADM, INFO3(VECTOR, NEEDVS, NEEDVT))
#define VMADN RSP_BUILD_OP(VMADN, VMADN, INFO3(VECTOR, NEEDVS, NEEDVT))
#define VMOV RSP_BUILD_OP(VMOV, VINVALID, INFO1(VECTOR))
#define VMRG RSP_BUILD_OP(VMRG, VMRG, INFO3(VECTOR, NEEDVS, NEEDVT))
#define VMUDH RSP_BUILD_OP(VMUDH, VMUDH, INFO3(VECTOR, NEEDVS, NEEDVT))
#define VMUDL RSP_BUILD_OP(VMUDL, VMUDL, INFO3(VECTOR, NEEDVS, NEEDVT))
#define VMUDM RSP_BUILD_OP(VMUDM, VMUDM, INFO3(VECTOR, NEEDVS, NEEDVT))
#define VMUDN RSP_BUILD_OP(VMUDN, VMUDN, INFO3(VECTOR, NEEDVS, NEEDVT))
#define VMULF RSP_BUILD_OP(VMULF, VMULF, INFO3(VECTOR, NEEDVS, NEEDVT))
#define VMULQ RSP_BUILD_OP(VMULQ, VINVALID, INFO1(VECTOR))
#define VMULU RSP_BUILD_OP(VMULU, VINVALID, INFO1(VECTOR))
#define VNAND RSP_BUILD_OP(VNAND, VNAND, INFO3(VECTOR, NEEDVS, NEEDVT))
#define VNE RSP_BUILD_OP(VNE, VNE, INFO3(VECTOR, NEEDVS, NEEDVT))
#define VNOP RSP_BUILD_OP(VNOP, VINVALID, INFO1(VECTOR))
#define VNOR RSP_BUILD_OP(VNOR, VNOR, INFO3(VECTOR, NEEDVS, NEEDVT))
#define VNXOR RSP_BUILD_OP(VNXOR, VNXOR, INFO3(VECTOR, NEEDVS, NEEDVT))
#define VOR RSP_BUILD_OP(VOR, VOR, INFO3(VECTOR, NEEDVS, NEEDVT))
#define VRCP RSP_BUILD_OP(VRCP, VINVALID, INFO1(VECTOR))
#define VRCPH RSP_BUILD_OP(VRCPH, VINVALID, INFO1(VECTOR))
#define VRCPL RSP_BUILD_OP(VRCPL, VINVALID, INFO1(VECTOR))
#define VRNDN RSP_BUILD_OP(VRNDN, VINVALID, INFO1(VECTOR))
#define VRNDP RSP_BUILD_OP(VRNDP, VINVALID, INFO1(VECTOR))
#define VRSQ RSP_BUILD_OP(VRSQ, VINVALID, INFO1(VECTOR))
#define VRSQH RSP_BUILD_OP(VRSQH, VINVALID, INFO1(VECTOR))
#define VRSQL RSP_BUILD_OP(VRSQL, VINVALID, INFO1(VECTOR))
#define VSAR RSP_BUILD_OP(VSAR, VSAR, INFO1(VECTOR))
#define VSUB RSP_BUILD_OP(VSUB, VSUB, INFO3(VECTOR, NEEDVS, NEEDVT))
#define VSUBC RSP_BUILD_OP(VSUBC, VSUBC, INFO3(VECTOR, NEEDVS, NEEDVT))
#define VXOR RSP_BUILD_OP(VXOR, VXOR, INFO3(VECTOR, NEEDVS, NEEDVT))

#define LBV RSP_BUILD_OP(LBV, BDLQSV_SBDLQSV, INFO3(NEEDRS, NEEDVT, LOAD))
#define LDV RSP_BUILD_OP(LDV, BDLQSV_SBDLQSV, INFO3(NEEDRS, NEEDVT, LOAD))
#define LFV RSP_BUILD_OP(LFV, INVALID, INFO1(NONE))
#define LHV RSP_BUILD_OP(LHV, INVALID, INFO1(NONE))
#define LLV RSP_BUILD_OP(LLV, BDLQSV_SBDLQSV, INFO3(NEEDRS, NEEDVT, LOAD))
#define LPV RSP_BUILD_OP(LPV, INVALID, INFO1(NONE))
#define LQV RSP_BUILD_OP(LQV, BDLQSV_SBDLQSV, INFO3(NEEDRS, NEEDVT, LOAD))
#define LRV RSP_BUILD_OP(LRV, INVALID, INFO1(NONE))
#define LSV RSP_BUILD_OP(LSV, BDLQSV_SBDLQSV, INFO3(NEEDRS, NEEDVT, LOAD))
#define LTV RSP_BUILD_OP(LTV, INVALID, INFO1(NONE))
#define LUV RSP_BUILD_OP(LUV, INVALID, INFO1(NONE))

#define SBV RSP_BUILD_OP(SBV, BDLQSV_SBDLQSV, INFO3(NEEDRS, NEEDVT, STORE))
#define SDV RSP_BUILD_OP(SDV, BDLQSV_SBDLQSV, INFO3(NEEDRS, NEEDVT, STORE))
#define SFV RSP_BUILD_OP(SFV, INVALID, INFO1(NONE))
#define SHV RSP_BUILD_OP(SHV, INVALID, INFO1(NONE))
#define SLV RSP_BUILD_OP(SLV, BDLQSV_SBDLQSV, INFO3(NEEDRS, NEEDVT, STORE))
#define SPV RSP_BUILD_OP(SPV, INVALID, INFO1(NONE))
#define SQV RSP_BUILD_OP(SQV, BDLQSV_SBDLQSV, INFO3(NEEDRS, NEEDVT, STORE))
#define SRV RSP_BUILD_OP(SRV, INVALID, INFO1(NONE))
#define SSV RSP_BUILD_OP(SSV, BDLQSV_SBDLQSV, INFO3(NEEDRS, NEEDVT, STORE))
#define STV RSP_BUILD_OP(STV, INVALID, INFO1(NONE))
#define SUV RSP_BUILD_OP(SUV, INVALID, INFO1(NONE))
#define SWV RSP_BUILD_OP(SWV, INVALID, INFO1(NONE))

#endif

