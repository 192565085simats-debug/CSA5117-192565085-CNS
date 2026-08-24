#include <stdio.h>
#include <stdint.h>

// Mock block cipher E_K
uint32_t blockCipherEncrypt(uint32_t block, uint32_t key) {
    return ((block ^ key) * 0x45D9F3B) ^ 0x9E3779B9;
}

// CBC-MAC for n blocks
uint32_t computeCBC_MAC(const uint32_t *blocks, int n, uint32_t key) {
    uint32_t mac = 0;
    for (int i = 0; i < n; i++) {
        mac = blockCipherEncrypt(mac ^ blocks[i], key);
    }
    return mac;
}

int main() {
    printf("===============================================================\n");
    printf("      EXP 30: CBC-MAC EXTENSION FORGERY ATTACK DEMONSTRATION   \n");
    printf("===============================================================\n\n");

    uint32_t secretKey = 0xDEADBEEF; // Unknown to adversary

    // 1. Single block message X
    uint32_t X = 0x12345678;
    uint32_t T = computeCBC_MAC(&X, 1, secretKey);

    printf("Legitimate Interaction:\n");
    printf("  Single-block Message X = 0x%08X\n", X);
    printf("  Valid CBC-MAC T        = 0x%08X\n\n", T);

    printf("================ ADVERSARY FORGERY ATTACK ================\n");
    printf("Adversary crafts a 2-block message without knowing secret key:\n");
    printf("  Block 1: M1 = X              = 0x%08X\n", X);
    printf("  Block 2: M2 = X ^ T          = 0x%08X ^ 0x%08X = 0x%08X\n\n", X, T, X ^ T);

    uint32_t forgedMessage[2] = { X, X ^ T };

    // Adversary claims MAC for forgedMessage is T
    printf("Adversary predicts CBC-MAC for forged 2-block message will be T (0x%08X).\n\n", T);

    // Verification by receiver
    uint32_t forgedMAC = computeCBC_MAC(forgedMessage, 2, secretKey);

    printf("Receiver Verification:\n");
    printf("  Step 1: C1 = E_K(M1)          = E_K(X) = T = 0x%08X\n", T);
    printf("  Step 2: Input to E_K in Step 2 = M2 ^ C1 = (X ^ T) ^ T = X\n");
    printf("  Step 3: C2 = E_K(X)           = T = 0x%08X\n\n", forgedMAC);

    if (forgedMAC == T) {
        printf(">>> FORGERY ATTACK SUCCESSFUL! <<<\n");
        printf("The adversary successfully forged a valid MAC for a new message\n");
        printf("without ever knowing the secret key.\n\n");
    }

    printf("Remedy / Mitigation:\n");
    printf("  Use CMAC (NIST SP 800-38B) or encrypt the final block with a derived subkey.\n");
    printf("===============================================================\n");

    return 0;
}
