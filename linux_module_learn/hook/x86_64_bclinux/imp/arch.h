#ifndef __ARCH_H
#define __ARCH_H

#if defined(__x86_64__)
#define __target_x86
#define __target_defined
#elif defined(__arm__)
#define __target_arm64
#define __target_defined
#elif defined(__aarch64__)
#define __target_arm64
#define __target_defined
#endif /* no compiler target */

#if defined(__target_defined)

#if defined(__target_x86)

#define PT_REGS_PARM1(x) ((x)->di)
#define PT_REGS_PARM2(x) ((x)->si)
#define PT_REGS_PARM3(x) ((x)->dx)
#define PT_REGS_PARM4(x) ((x)->r10)
#define PT_REGS_PARM5(x) ((x)->r8)
#define PT_REGS_PARM6(x) ((x)->r9)

#elif defined(__target_arm64)

#define PT_REGS_PARM1(x) ((x)->regs[0])
#define PT_REGS_PARM2(x) ((x)->regs[1])
#define PT_REGS_PARM3(x) ((x)->regs[2])
#define PT_REGS_PARM4(x) ((x)->regs[3])
#define PT_REGS_PARM5(x) ((x)->regs[4])
#define PT_REGS_PARM6(x) ((x)->regs[5])

#endif

#endif /* __target_defined */

#endif /* __ARCH_H */
