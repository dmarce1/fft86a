#define       X              %rdi
#define       S              %r8
#define       Wr             %r9
#define       Wi             %r10
#define       flag           %r11
#define       er0            %ymm0
#define       er1            %ymm1
#define       er2            %ymm2
#define       er3            %ymm3
#define       ei0            %ymm4
#define       ei1            %ymm5
#define       ei2            %ymm6
#define       ei3            %ymm7
#define       tr0            %ymm8
#define       ti0            %ymm9
#define       tr1            %ymm10
#define       ti1            %ymm11
#define       tr2            %ymm12
#define       ti2            %ymm13
#define       tr3            %ymm14
#define       ti3            %ymm15
#define       cos1           %ymm10
#define       sin1           %ymm11
#define       cos2           %ymm12
#define       sin2           %ymm13
#define       two            %ymm14

              .global        radix4_dit
              .global        radix4_dif
              .global        radix2_dit
              .global        radix2_dif

              .text

              .align         32
TWO:          .double        2.0
              .double        2.0
              .double        2.0
              .double        2.0

radix4_dit:   push           %rbx
              mov            %r8, flag
              mov            %rcx, Wi
              mov            %rdx, Wr
              mov            %rsi, S
              vmovupd        TWO, two
              lea            (X), %rax
              lea            (%rax, S, 8), %rbx
              lea            (%rbx, S, 8), %rcx
              lea            (%rcx, S, 8), %rdx
              vmovupd        (%rax), er0
              vmovupd        (%rbx), er2
              vmovupd        (%rcx), er1
              vmovupd        (%rdx), er3
              vmovupd        32(%rax), ei0
              vmovupd        32(%rbx), ei2
              vmovupd        32(%rcx), ei1
              vmovupd        32(%rdx), ei3
              test           $2, flag
              jz             L1
              vpermpd        $216, er0, tr0
              vpermpd        $216, ei0, ti0
              vperm2f128     $0x20, ti0, tr0, er0
              vperm2f128     $0x31, ti0, tr0, ei0
              vpermpd        $216, er1, tr0
              vpermpd        $216, ei1, ti0
              vperm2f128     $0x20, ti0, tr0, er1
              vperm2f128     $0x31, ti0, tr0, ei1
              vpermpd        $216, er2, tr0
              vpermpd        $216, ei2, ti0
              vperm2f128     $0x20, ti0, tr0, er2
              vperm2f128     $0x31, ti0, tr0, ei2
              vpermpd        $216, er3, tr0
              vpermpd        $216, ei3, ti0
              vperm2f128     $0x20, ti0, tr0, er3
              vperm2f128     $0x31, ti0, tr0, ei3
L1:           vmovupd        32(Wr), cos1
              vmovupd        64(Wr), cos2
              vmovupd        32(Wi), sin1
              vmovupd        64(Wi), sin2
              vmovupd        er0, tr0
              vmovupd        ei0, ti0
              vfmadd231pd    sin2, ei2, tr0
              vfnmadd231pd   sin2, er2, ti0
              vfnmadd132pd   cos2, tr0, er2
              vfnmadd132pd   cos2, ti0, ei2
              vfmsub132pd    two, er2, er0
              vfmsub132pd    two, ei2, ei0
              vmovupd        er1, tr0
              vmovupd        ei1, ti0
              vfmadd231pd    sin2, ei3, tr0
              vfnmadd231pd   sin2, er3, ti0
              vfnmadd132pd   cos2, tr0, er3
              vfnmadd132pd   cos2, ti0, ei3
              vfmsub132pd    two, er3, er1
              vfmsub132pd    two, ei3, ei1
              vmovupd        er0, tr0
              vmovupd        ei0, ti0
              vfmadd231pd    sin1, ei1, tr0
              vfnmadd231pd   sin1, er1, ti0
              vfnmadd132pd   cos1, tr0, er1
              vfnmadd132pd   cos1, ti0, ei1
              vfmsub132pd    two, er1, er0
              vfmsub132pd    two, ei1, ei0
              vmovupd        er2, tr0
              vmovupd        ei2, ti0
              vfmadd231pd    cos1, ei3, tr0
              vfnmadd231pd   cos1, er3, ti0
              vfmadd132pd    sin1, tr0, er3
              vfmadd132pd    sin1, ti0, ei3
              vfmsub132pd    two, er3, er2
              vfmsub132pd    two, ei3, ei2
              test           $1, flag
              jz             L2
              vperm2f128     $0x20, ei0, er0, tr0
              vperm2f128     $0x31, ei0, er0, ti0
              vpermpd        $216, tr0, er0
              vpermpd        $216, ti0, ei0
              vperm2f128     $0x20, ei1, er1, tr0
              vperm2f128     $0x31, ei1, er1, ti0
              vpermpd        $216, tr0, er1
              vpermpd        $216, ti0, ei1
              vperm2f128     $0x20, ei2, er2, tr0
              vperm2f128     $0x31, ei2, er2, ti0
              vpermpd        $216, tr0, er2
              vpermpd        $216, ti0, ei2
              vperm2f128     $0x20, ei3, er3, tr0
              vperm2f128     $0x31, ei3, er3, ti0
              vpermpd        $216, tr0, er3
              vpermpd        $216, ti0, ei3
L2:           vmovupd        er0, (%rax)
              vmovupd        er3, (%rbx)
              vmovupd        er1, (%rcx)
              vmovupd        er2, (%rdx)
              vmovupd        ei0, 32(%rax)
              vmovupd        ei3, 32(%rbx)
              vmovupd        ei1, 32(%rcx)
              vmovupd        ei2, 32(%rdx)
              pop            %rbx
              ret


radix4_dif:   push           %rbx
              mov            %r8, flag
              mov            %rcx, Wi
              mov            %rdx, Wr
              mov            %rsi, S
              lea            (X), %rax
              lea            (%rax, S, 8), %rbx
              lea            (%rbx, S, 8), %rcx
              lea            (%rcx, S, 8), %rdx
              vmovupd        (%rax), er0
              vmovupd        (%rbx), er1
              vmovupd        (%rcx), er2
              vmovupd        (%rdx), er3
              vmovupd        32(%rax), ei0
              vmovupd        32(%rbx), ei1
              vmovupd        32(%rcx), ei2
              vmovupd        32(%rdx), ei3
              test           $2, flag
              jz             L3
              vpermpd        $216, er0, tr0
              vpermpd        $216, ei0, ti0
              vperm2f128     $0x20, ti0, tr0, er0
              vperm2f128     $0x31, ti0, tr0, ei0
              vpermpd        $216, er1, tr0
              vpermpd        $216, ei1, ti0
              vperm2f128     $0x20, ti0, tr0, er1
              vperm2f128     $0x31, ti0, tr0, ei1
              vpermpd        $216, er2, tr0
              vpermpd        $216, ei2, ti0
              vperm2f128     $0x20, ti0, tr0, er2
              vperm2f128     $0x31, ti0, tr0, ei2
              vpermpd        $216, er3, tr0
              vpermpd        $216, ei3, ti0
              vperm2f128     $0x20, ti0, tr0, er3
              vperm2f128     $0x31, ti0, tr0, ei3
L3:           vaddpd         er2, er0, tr0
              vaddpd         ei2, ei0, ti0
              vsubpd         er2, er0, tr2
              vsubpd         ei2, ei0, ti2
              vaddpd         er3, er1, tr1
              vaddpd         ei3, ei1, ti1
              vsubpd         er3, er1, tr3
              vsubpd         ei3, ei1, ti3
              vaddpd         tr1, tr0, er0
              vaddpd         ti1, ti0, ei0
              vaddpd         ti3, tr2, er2
              vsubpd         tr3, ti2, ei2
              vsubpd         tr1, tr0, er1
              vsubpd         ti1, ti0, ei1
              vsubpd         ti3, tr2, er3
              vaddpd         tr3, ti2, ei3
              vmovupd        32(Wr), tr2
              vmovupd        64(Wr), tr1
              vmovupd        96(Wr), tr3
              vmovupd        32(Wi), ti2
              vmovupd        64(Wi), ti1
              vmovupd        96(Wi), ti3
              vmovupd        er1, tr0
              vmovupd        ei1, ti0
              vmulpd         ti1, ti0, er1
              vmulpd         tr1, ti0, ei1
              vfmsub231pd    tr1, tr0, er1
              vfmadd231pd    ti1, tr0, ei1
              vmovupd        er2, tr0
              vmovupd        ei2, ti0
              vmulpd         ti2, ti0, er2
              vmulpd         tr2, ti0, ei2
              vfmsub231pd    tr2, tr0, er2
              vfmadd231pd    ti2, tr0, ei2
              vmovupd        er3, tr0
              vmovupd        ei3, ti0
              vmulpd         ti3, ti0, er3
              vmulpd         tr3, ti0, ei3
              vfmsub231pd    tr3, tr0, er3
              vfmadd231pd    ti3, tr0, ei3
              vmovupd        er0, (%rax)
              vmovupd        er1, (%rbx)
              vmovupd        er2, (%rcx)
              vmovupd        er3, (%rdx)
              vmovupd        ei0, 32(%rax)
              vmovupd        ei1, 32(%rbx)
              vmovupd        ei2, 32(%rcx)
              vmovupd        ei3, 32(%rdx)
              pop            %rbx
              ret

radix2_dit:   push           %rbx
              mov            %r8, flag
              mov            %rcx, Wi
              mov            %rdx, Wr
              mov            %rsi, S
              vmovupd        TWO, two
              lea            (X), %rax
              lea            (%rax, S, 8), %rbx
              vmovupd        (%rax), er0
              vmovupd        (%rbx), er1
              vmovupd        32(%rax), ei0
              vmovupd        32(%rbx), ei1
              test           $2, flag
              jz             L4
              vpermpd        $216, er0, tr0
              vpermpd        $216, ei0, ti0
              vperm2f128     $0x20, ti0, tr0, er0
              vperm2f128     $0x31, ti0, tr0, ei0
              vpermpd        $216, er1, tr0
              vpermpd        $216, ei1, ti0
              vperm2f128     $0x20, ti0, tr0, er1
              vperm2f128     $0x31, ti0, tr0, ei1
L4:           vmovupd        32(Wr), cos1
              vmovupd        32(Wi), sin1
              vmovupd        er0, tr0
              vmovupd        ei0, ti0
              vfmadd231pd    sin1, ei1, tr0
              vfnmadd231pd   sin1, er1, ti0
              vfnmadd132pd   cos1, tr0, er1
              vfnmadd132pd   cos1, ti0, ei1
              vfmsub132pd    two, er1, er0
              vfmsub132pd    two, ei1, ei0
              test           $1, flag
              jz             L5
              vperm2f128     $0x20, ei0, er0, tr0
              vperm2f128     $0x31, ei0, er0, ti0
              vpermpd        $216, tr0, er0
              vpermpd        $216, ti0, ei0
              vperm2f128     $0x20, ei1, er1, tr1
              vperm2f128     $0x31, ei1, er1, ti1
              vpermpd        $216, tr1, er1
              vpermpd        $216, ti1, ei1
L5:           vmovupd        er0, (%rax)
              vmovupd        er1, (%rbx)
              vmovupd        ei0, 32(%rax)
              vmovupd        ei1, 32(%rbx)
              pop            %rbx
              ret

radix2_dif:   push           %rbx
              mov            %r8, flag
              mov            %rcx, Wi
              mov            %rdx, Wr
              mov            %rsi, S
              lea            (X), %rax
              lea            (%rax, S, 8), %rbx
              vmovupd        (%rax), er0
              vmovupd        (%rbx), er1
              vmovupd        32(%rax), ei0
              vmovupd        32(%rbx), ei1
              test           $2, flag
              jz             L7
              vpermpd        $216, er0, tr0
              vpermpd        $216, ei0, ti0
              vperm2f128     $0x20, ti0, tr0, er0
              vperm2f128     $0x31, ti0, tr0, ei0
              vpermpd        $216, er1, tr0
              vpermpd        $216, ei1, ti0
              vperm2f128     $0x20, ti0, tr0, er1
              vperm2f128     $0x31, ti0, tr0, ei1
L7:           vaddpd         er1, er0, tr0
              vaddpd         ei1, ei0, ti0
              vsubpd         er1, er0, tr1
              vsubpd         ei1, ei0, ti1
              vmovupd        32(Wr), er1
              vmovupd        32(Wi), ei1
              vmovupd        tr1, er0
              vmovupd        ti1, ei0
              vmulpd         ei1, ei0, tr1
              vmulpd         er1, ei0, ti1
              vfmsub231pd    er1, er0, tr1
              vfmadd231pd    ei1, er0, ti1
              vmovupd        tr0, (%rax)
              vmovupd        tr1, (%rbx)
              vmovupd        ti0, 32(%rax)
              vmovupd        ti1, 32(%rbx)
              pop            %rbx
              ret


