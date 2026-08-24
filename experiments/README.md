# Cryptography & Network Security (CNS) Lab Experiments

This repository contains full C implementations, theoretical proofs, and test vectors for all 40 CNS lab experiments.

## Index of Experiments

| Experiment | Directory | Description |
| :--- | :--- | :--- |
| **EXP 01** | [`EXP01 - Caesar Cipher`](./EXP01%20-%20Caesar%20Cipher/code.c) | Classical Caesar Cipher encryption and decryption with key $k \in [1, 25]$. |
| **EXP 02** | [`EXP02 - Monoalphabetic Substitution Cipher`](./EXP02%20-%20Monoalphabetic%20Substitution%20Cipher/code.c) | Monoalphabetic substitution cipher with custom/QWERTY 26-letter substitution mapping. |
| **EXP 03** | [`EXP03 - Playfair Cipher`](./EXP03%20-%20Playfair%20Cipher/code.c) | Playfair cipher 5x5 matrix generation from keyword, digraph padding ('X'), encryption and decryption. |
| **EXP 04** | [`EXP04 - Polyalphabetic Cipher`](./EXP04%20-%20Polyalphabetic%20Cipher/code.c) | Vigenère polyalphabetic cipher encryption and decryption with periodic keyword. |
| **EXP 05** | [`EXP05 - Affine Caesar Cipher`](./EXP05%20-%20Affine%20Caesar%20Cipher/code.c) | Affine Caesar cipher $C = (ap + b) \bmod 26$, modular inverse calculation, and parameter validation. |
| **EXP 06** | [`EXP06 - Break Affine Cipher`](./EXP06%20-%20Break%20Affine%20Cipher/code.c) | Cryptanalysis of Affine cipher using frequency analysis ('B' = 1st, 'U' = 2nd most frequent). |
| **EXP 07** | [`EXP07 - Simple Substitution Decryption`](./EXP07%20-%20Simple%20Substitution%20Decryption/code.c) | Decryption of Edgar Allan Poe's classic Gold-Bug substitution cipher text. |
| **EXP 08** | [`EXP08 - Keyword Based Monoalphabetic Cipher`](./EXP08%20-%20Keyword%20Based%20Monoalphabetic%20Cipher/code.c) | Monoalphabetic cipher alphabet generated from keyword (`CIPHER`). |
| **EXP 09** | [`EXP09 - Playfair Decryption PT-109`](./EXP09%20-%20Playfair%20Decryption%20PT-109/code.c) | Decryption of JFK's WWII PT-109 wireless message using key `ROYAL NEW ZEALAND NAVY`. |
| **EXP 10** | [`EXP10 - Playfair Matrix Encryption`](./EXP10%20-%20Playfair%20Matrix%20Encryption/code.c) | Playfair encryption using a predefined 5x5 matrix. |
| **EXP 11** | [`EXP11 - Playfair Key Space Analysis`](./EXP11%20-%20Playfair%20Key%20Space%20Analysis/code.c) | Theoretical keys ($25! \approx 2^{84}$) vs. effectively unique keys ($24! \approx 2^{79}$) calculation. |
| **EXP 12** | [`EXP12 - Hill Cipher 2x2`](./EXP12%20-%20Hill%20Cipher%202x2/code.c) | 2x2 Hill cipher encryption and decryption with modular matrix inversion. |
| **EXP 13** | [`EXP13 - Known Plaintext Attack on Hill Cipher`](./EXP13%20-%20Known%20Plaintext%20Attack%20on%20Hill%20Cipher/code.c) | Recovery of 2x2 Hill cipher secret key matrix $K = P^{-1} \cdot C \pmod{26}$. |
| **EXP 14** | [`EXP14 - One-Time Pad Vigenere`](./EXP14%20-%20One-Time%20Pad%20Vigenere/code.c) | One-time pad with numerical key streams and perfect secrecy demonstrations. |
| **EXP 15** | [`EXP15 - Frequency Attack on Additive Cipher`](./EXP15%20-%20Frequency%20Attack%20on%20Additive%20Cipher/code.c) | Automated letter frequency attack with Chi-squared scoring returning top $N$ plaintexts. |
| **EXP 16** | [`EXP16 - Frequency Attack on Monoalphabetic Cipher`](./EXP16%20-%20Frequency%20Attack%20on%20Monoalphabetic%20Cipher/code.c) | Frequency attack on monoalphabetic substitution ciphers. |
| **EXP 17** | [`EXP17 - DES Decryption Key Schedule`](./EXP17%20-%20DES%20Decryption%20Key%20Schedule/code.c) | Right-shift key generation schedule for reverse DES decryption round keys ($K_{16} \to K_1$). |
| **EXP 18** | [`EXP18 - DES Subkey Disjoint Subset`](./EXP18%20-%20DES%20Subkey%20Disjoint%20Subset/code.c) | Proof that DES subkey halves originate from disjoint 28-bit sets ($C_0$ and $D_0$). |
| **EXP 19** | [`EXP19 - 3DES in CBC Mode`](./EXP19%20-%203DES%20in%20CBC%20Mode/code.c) | Triple DES (EDE) in CBC mode with security vs. performance analysis. |
| **EXP 20** | [`EXP20 - Error Propagation in ECB vs CBC`](./EXP20%20-%20Error%20Propagation%20in%20ECB%20vs%20CBC/code.c) | Error propagation simulation in ECB vs CBC modes. |
| **EXP 21** | [`EXP21 - Block Cipher Padding`](./EXP21%20-%20Block%20Cipher%20Padding/code.c) | PKCS#7 & 1-bit padding methods with unambiguous unpadding analysis. |
| **EXP 22** | [`EXP22 - S-DES in CBC Mode`](./EXP22%20-%20S-DES%20in%20CBC%20Mode/code.c) | Simplified DES (S-DES) in CBC mode verified against test vectors. |
| **EXP 23** | [`EXP23 - S-DES in Counter Mode`](./EXP23%20-%20S-DES%20in%20Counter%20Mode/code.c) | S-DES in Counter (CTR) mode verified against test vectors. |
| **EXP 24** | [`EXP24 - RSA Private Key Generation`](./EXP24%20-%20RSA%20Private%20Key%20Generation/code.c) | RSA key calculation for $e = 31, n = 3599$ via factoring and Extended Euclidean algorithm. |
| **EXP 25** | [`EXP25 - RSA Common Factor Vulnerability`](./EXP25%20-%20RSA%20Common%20Factor%20Vulnerability/code.c) | Factoring RSA modulus $n$ and key extraction given $\gcd(P, n) > 1$. |
| **EXP 26** | [`EXP26 - RSA Modulus Reuse Vulnerability`](./EXP26%20-%20RSA%20Modulus%20Reuse%20Vulnerability/code.c) | Proof and demonstration of why reusing modulus $n$ after leaking $d$ is insecure. |
| **EXP 27** | [`EXP27 - RSA Single Character Encryption Attack`](./EXP27%20-%20RSA%20Single%20Character%20Encryption%20Attack/code.c) | Dictionary/codebook attack on single-character RSA encryptions. |
| **EXP 28** | [`EXP28 - Diffie-Hellman Protocol Analysis`](./EXP28%20-%20Diffie-Hellman%20Protocol%20Analysis/code.c) | Standard DH ($g^x \bmod q$) vs. flawed alternative ($x^g \bmod q$) root attack. |
| **EXP 29** | [`EXP29 - SHA-3 Capacity Absorption Simulation`](./EXP29%20-%20SHA-3%20Capacity%20Absorption%20Simulation/code.c) | SHA-3/Keccak state diffusion and capacity absorption simulation. |
| **EXP 30** | [`EXP30 - CBC-MAC Extension Attack`](./EXP30%20-%20CBC-MAC%20Extension%20Attack/code.c) | MAC forgery attack demonstration on raw CBC-MAC. |
| **EXP 31** | [`EXP31 - CMAC Subkey Generation`](./EXP31%20-%20CMAC%20Subkey%20Generation/code.c) | CMAC subkey derivation with $R_b$ constants for 64-bit and 128-bit ciphers. |
| **EXP 32** | [`EXP32 - DSA vs RSA Signature Non-Determinism`](./EXP32%20-%20DSA%20vs%20RSA%20Signature%20Non-Determinism/code.c) | DSA per-signature ephemeral key randomness and catastrophic $k$-reuse attack. |
| **EXP 33** | [`EXP33 - DES Implementation`](./EXP33%20-%20DES%20Implementation/code.c) | Complete 64-bit DES implementation with standard Feistel rounds and S-boxes. |
| **EXP 34** | [`EXP34 - Padding Necessity in Block Ciphers`](./EXP34%20-%20Padding%20Necessity%20in%20Block%20Ciphers/code.c) | Unambiguous unpadding demonstration comparing padded vs. unpadded streams. |
| **EXP 35** | [`EXP35 - One-Time Pad Numerical Key Stream`](./EXP35%20-%20One-Time%20Pad%20Numerical%20Key%20Stream/code.c) | Numerical OTP stream cipher with random keys and perfect secrecy. |
| **EXP 36** | [`EXP36 - Affine Cipher Invertibility Conditions`](./EXP36%20-%20Affine%20Cipher%20Invertibility%20Conditions/code.c) | Affine cipher collision proof ($a=2, b=3$) and full $\gcd(a, 26) = 1$ parameter validation. |
| **EXP 37** | [`EXP37 - Monoalphabetic Frequency Analysis`](./EXP37%20-%20Monoalphabetic%20Frequency%20Analysis/code.c) | Automated monoalphabetic cryptanalysis with frequency alignment ranking. |
| **EXP 38** | [`EXP38 - Hill Cipher Chosen Plaintext Attack`](./EXP38%20-%20Hill%20Cipher%20Chosen%20Plaintext%20Attack/code.c) | Chosen plaintext attack on Hill cipher using standard basis vectors. |
| **EXP 39** | [`EXP39 - Additive Cipher Top-10 Frequency Attack`](./EXP39%20-%20Additive%20Cipher%20Top-10%20Frequency%20Attack/code.c) | Additive cipher automated frequency scoring and top-10 candidate extraction. |
| **EXP 40** | [`EXP40 - Advanced Monoalphabetic Substitution Attack`](./EXP40%20-%20Advanced%20Monoalphabetic%20Substitution%20Attack/code.c) | Advanced frequency analysis attack on monoalphabetic substitution ciphers. |
