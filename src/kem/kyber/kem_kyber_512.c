#include <stdlib.h>

#include <oqs/kem_kyber.h>

#ifdef OQS_ENABLE_KEM_kyber_512

OQS_KEM *OQS_KEM_kyber_512_new() {

	OQS_KEM *kem = malloc(sizeof(OQS_KEM));
	if (kem == NULL) {
		return NULL;
	}
	kem->method_name = OQS_KEM_alg_kyber_512;
	kem->alg_version = "https://github.com/pq-crystals/kyber/commit/46e283ab575ec92dfe82fb12229ae2d9d6246682";

	kem->claimed_nist_level = 1;
	kem->ind_cca = true;

	kem->length_public_key = OQS_KEM_kyber_512_length_public_key;
	kem->length_secret_key = OQS_KEM_kyber_512_length_secret_key;
	kem->length_ciphertext = OQS_KEM_kyber_512_length_ciphertext;
	kem->length_shared_secret = OQS_KEM_kyber_512_length_shared_secret;

	kem->keypair = OQS_KEM_kyber_512_keypair;
	kem->encaps = OQS_KEM_kyber_512_encaps;
	kem->decaps = OQS_KEM_kyber_512_decaps;

	return kem;
}


int PQCLEAN_KYBER512_CLEAN_crypto_kem_keypair(unsigned char *pk, unsigned char *sk);
int PQCLEAN_KYBER512_CLEAN_crypto_kem_enc(unsigned char *ct, unsigned char *ss, const unsigned char *pk);
int PQCLEAN_KYBER512_CLEAN_crypto_kem_dec(unsigned char *ss, const unsigned char *ct, const unsigned char *sk);

#if defined(OQS_ENABLE_KEM_kyber_512_avx2)
int PQCLEAN_KYBER512_AVX2_crypto_kem_keypair(unsigned char *pk, unsigned char *sk);
int PQCLEAN_KYBER512_AVX2_crypto_kem_enc(unsigned char *ct, unsigned char *ss, const unsigned char *pk);
int PQCLEAN_KYBER512_AVX2_crypto_kem_dec(unsigned char *ss, const unsigned char *ct, const unsigned char *sk);
#endif


OQS_API OQS_STATUS OQS_KEM_kyber_512_keypair(uint8_t *public_key, uint8_t *secret_key) {
#ifdef OQS_ENABLE_KEM_kyber_512_avx2
#ifdef OQS_ENABLE_CPUFEATURES
	if (OQS_RT_cpu_flags().AVX2_INSTRUCTIONS  && OQS_RT_cpu_flags().BMI2_INSTRUCTIONS ) {
		return (OQS_STATUS) PQCLEAN_KYBER512_AVX2_crypto_kem_keypair(public_key, secret_key);
	} else {
		return (OQS_STATUS) PQCLEAN_KYBER512_CLEAN_crypto_kem_keypair(public_key, secret_key);
	}
#else
	return (OQS_STATUS) PQCLEAN_KYBER512_AVX2_crypto_kem_keypair(public_key, secret_key);
#endif
#else
// Assume CLEAN always compiles
	return (OQS_STATUS) PQCLEAN_KYBER512_CLEAN_crypto_kem_keypair(public_key, secret_key);
#endif
}

OQS_API OQS_STATUS OQS_KEM_kyber_512_encaps(uint8_t *ciphertext, uint8_t *shared_secret, const uint8_t *public_key) {
#ifdef OQS_ENABLE_KEM_kyber_512_avx2
#ifdef OQS_ENABLE_CPUFEATURES
	if (OQS_RT_cpu_flags().AVX2_INSTRUCTIONS  && OQS_RT_cpu_flags().BMI2_INSTRUCTIONS ) {
		return (OQS_STATUS) PQCLEAN_KYBER512_AVX2_crypto_kem_enc(ciphertext, shared_secret, public_key);
	} else {
		return (OQS_STATUS) PQCLEAN_KYBER512_CLEAN_crypto_kem_enc(ciphertext, shared_secret, public_key);
	}
#else
	return (OQS_STATUS) PQCLEAN_KYBER512_AVX2_crypto_kem_enc(ciphertext, shared_secret, public_key);
#endif
#else
// Assume CLEAN always compiles
	return (OQS_STATUS) PQCLEAN_KYBER512_CLEAN_crypto_kem_enc(ciphertext, shared_secret, public_key);
#endif
}

OQS_API OQS_STATUS OQS_KEM_kyber_512_decaps(uint8_t *shared_secret, const unsigned char *ciphertext, const uint8_t *secret_key) {
#ifdef OQS_ENABLE_KEM_kyber_512_avx2
#ifdef OQS_ENABLE_CPUFEATURES
	if (OQS_RT_cpu_flags().AVX2_INSTRUCTIONS  && OQS_RT_cpu_flags().BMI2_INSTRUCTIONS ) {
		return (OQS_STATUS) PQCLEAN_KYBER512_AVX2_crypto_kem_dec(shared_secret, ciphertext, secret_key);
	} else {
		return (OQS_STATUS) PQCLEAN_KYBER512_CLEAN_crypto_kem_dec(shared_secret, ciphertext, secret_key);
	}
#else
	return (OQS_STATUS) PQCLEAN_KYBER512_AVX2_crypto_kem_dec(shared_secret, ciphertext, secret_key);
#endif
#else
// Assume CLEAN always compiles
	return (OQS_STATUS) PQCLEAN_KYBER512_CLEAN_crypto_kem_dec(shared_secret, ciphertext, secret_key);
#endif
}

#endif
