    .section .text
    .globl countPulseASM
countPulseASM:
    addi sp, sp, -24      # Allocate stack space (3 registers: s1, s2, ra)
    sd s1, 16(sp)         # Save s1 (preserved register)
    sd s2, 8(sp)          # Save s2 (preserved register)
    sd ra, 0(sp)          # Save return address

    mv s1, a3             # s1 = maxloops
    mv s2, zero           # s2 = width (initialize to 0)

# Wait for previous pulse to end
loop1:
    ld t0, 0(a0)          # t0 = *port
    and t0, t0, a1        # t0 = (*port & bit)
    bne t0, a2, loop2     # if (t0 != stateMask) break
    addi s1, s1, -1       # maxloops--
    beqz s1, timeout      # if maxloops == 0, return 0
    j loop1               # Repeat

# Wait for pulse to start
loop2:
    ld t0, 0(a0)          # t0 = *port
    and t0, t0, a1        # t0 = (*port & bit)
    beq t0, a2, loop3     # if (t0 == stateMask) break
    addi s1, s1, -1       # maxloops--
    beqz s1, timeout      # if maxloops == 0, return 0
    j loop2               # Repeat

# Measure pulse duration
loop3:
    ld t0, 0(a0)          # t0 = *port
    and t0, t0, a1        # t0 = (*port & bit)
    bne t0, a2, done      # if (t0 != stateMask), exit loop
    addi s2, s2, 1        # width++
    bge s2, s1, timeout   # if (width >= maxloops), return 0
    j loop3               # Repeat

done:
    mv a0, s2             # Return width
    j end

timeout:
    mv a0, zero           # Return 0

end:
    ld ra, 0(sp)          # Restore return address
    ld s2, 8(sp)          # Restore s2
    ld s1, 16(sp)         # Restore s1
    addi sp, sp, 24       # Restore stack
    jr ra                 # Return
