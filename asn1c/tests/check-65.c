#undef	NDEBUG
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <assert.h>

#include <T.h>
#include <T1.h>

uint8_t buf1[] = {
	32 | ((2 << 6) + 2),	/* [2], constructed */
	8,
	32 | ((2 << 6) + 3),	/* [3], constructed */
	6,
	32 | ((2 << 6) + 4),	/* [4], constructed */
	4,
	0  | ((2 << 6) + 6),	/* [6], primitive */
	2,
  0x91,
  0x92
};

uint8_t buf2[] = {

	32 | ((2 << 6) + 0),	/* [0], constructed */
	22,

	32 | ((2 << 6) + 1),	/* [1], constructed */
	6,
	32 | ((2 << 6) + 4),	/* [4], constructed */
	4,
	0  | ((2 << 6) + 6),	/* [6], primitive */
	2,
  0x91,
  0x92,

	32 | ((2 << 6) + 2),	/* [2], constructed */
	6,
	32 | ((2 << 6) + 4),	/* [4], constructed */
	4,
	0  | ((2 << 6) + 6),	/* [6], primitive */
	2,
  0x91,
  0x92,

	32 | ((2 << 6) + 3),	/* [3], constructed */
	4,
	0  | ((2 << 6) + 6),	/* [6], primitive */
	2,
  0x91,
  0x92,

};

static void
check_1(int is_ok, uint8_t *buf, int size, size_t consumed) {
	asn1_TYPE_descriptor_t *td = &asn1_DEF_T1;
	ber_dec_rval_t rval;
	T1_t t, *tp;

	tp = memset(&t, 0, sizeof(t));

	fprintf(stderr, "Buf %p\n", buf);
	rval = ber_decode(td, (void **)&tp, buf, size);
	fprintf(stderr, "Returned code %d, consumed %d\n",
		(int)rval.code, (int)rval.consumed);

	if(is_ok) {
		assert(rval.code == RC_OK);
		assert(rval.consumed == consumed);
	} else {
		if(rval.code == RC_OK) {
		}
		assert(rval.consumed <= consumed);
	}
}

static void
check_2(int is_ok, uint8_t *buf, int size, size_t consumed) {
	asn1_TYPE_descriptor_t *td = &asn1_DEF_T;
	ber_dec_rval_t rval;
	T_t t, *tp;

	tp = memset(&t, 0, sizeof(t));

	fprintf(stderr, "Buf %p\n", buf);
	rval = ber_decode(td, (void **)&tp, buf, size);
	fprintf(stderr, "Returned code %d, consumed %d\n",
		(int)rval.code, (int)rval.consumed);

	if(is_ok) {
		assert(rval.code == RC_OK);
		assert(rval.consumed == consumed);
	} else {
		if(rval.code == RC_OK) {
		}
		assert(rval.consumed <= consumed);
	}
}

int
main(int ac, char **av) {

	(void)ac;	/* Unused argument */
	(void)av;	/* Unused argument */

	check_1(1, buf1, sizeof(buf1), sizeof(buf1));
	check_1(0, buf1, sizeof(buf1) - 1, sizeof(buf1) - 1);

	check_2(1, buf2, sizeof(buf2), sizeof(buf2));
	check_2(0, buf2, sizeof(buf2) - 1, sizeof(buf2) - 1);

	return 0;
}