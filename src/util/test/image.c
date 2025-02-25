/* Copyright (c) 2013-2023 Jeffrey Pfau
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#include "util/test/suite.h"

#include <mgba-util/image.h>

M_TEST_DEFINE(pitchRead) {
	static uint8_t buffer[12] = {
		0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xA, 0xB
	};

	struct mImage image = {
		.data = buffer,
		.height = 1
	};
	int i;

	image.depth = 1;
	image.width = 12;
	image.format = mCOLOR_L8;

	for (i = 0; i < 12; ++i) {
		assert_int_equal(mImageGetPixelRaw(&image, i, 0), i);
	}

	image.depth = 2;
	image.width = 6;
	image.format = mCOLOR_RGB5;

	for (i = 0; i < 6; ++i) {
#ifdef __BIG_ENDIAN__
		assert_int_equal(mImageGetPixelRaw(&image, i, 0), (i * 2) << 8 | (i * 2 + 1));
#else
		assert_int_equal(mImageGetPixelRaw(&image, i, 0), (i * 2 + 1) << 8 | (i * 2));
#endif
	}

	image.depth = 3;
	image.width = 4;
	image.format = mCOLOR_RGB8;

	for (i = 0; i < 4; ++i) {
#ifdef __BIG_ENDIAN__
		assert_int_equal(mImageGetPixelRaw(&image, i, 0), (i * 3) << 16 | (i * 3 + 1) << 8 | (i * 3 + 2));
#else
		assert_int_equal(mImageGetPixelRaw(&image, i, 0), (i * 3 + 2) << 16 | (i * 3 + 1) << 8 | (i * 3));
#endif
	}

	image.depth = 4;
	image.width = 3;
	image.format = mCOLOR_ARGB8;

	for (i = 0; i < 3; ++i) {
#ifdef __BIG_ENDIAN__
		assert_int_equal(mImageGetPixelRaw(&image, i, 0), (i * 4) << 24 | (i * 4 + 1) << 16 | (i * 4 + 2) << 8 | (i * 4 + 3));
#else
		assert_int_equal(mImageGetPixelRaw(&image, i, 0), (i * 4 + 3) << 24 | (i * 4 + 2) << 16 | (i * 4 + 1) << 8 | (i * 4));
#endif
	}
}

M_TEST_DEFINE(strideRead) {
	static uint8_t buffer[12] = {
		0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xA, 0xB
	};

	struct mImage image = {
		.data = buffer,
		.width = 1
	};
	int i;

	image.depth = 1;
	image.stride = 1;
	image.height = 12;
	image.format = mCOLOR_L8;

	for (i = 0; i < 12; ++i) {
		assert_int_equal(mImageGetPixelRaw(&image, 0, i), i);
	}

	image.depth = 1;
	image.stride = 2;
	image.height = 6;
	image.format = mCOLOR_L8;

	for (i = 0; i < 6; ++i) {
		assert_int_equal(mImageGetPixelRaw(&image, 0, i), i * 2);
	}

	image.depth = 2;
	image.stride = 1;
	image.height = 6;
	image.format = mCOLOR_RGB5;

	for (i = 0; i < 6; ++i) {
#ifdef __BIG_ENDIAN__
		assert_int_equal(mImageGetPixelRaw(&image, 0, i), (i * 2) << 8 | (i * 2 + 1));
#else
		assert_int_equal(mImageGetPixelRaw(&image, 0, i), (i * 2 + 1) << 8 | (i * 2));
#endif
	}

	image.depth = 2;
	image.stride = 2;
	image.height = 3;
	image.format = mCOLOR_RGB5;

	for (i = 0; i < 3; ++i) {
#ifdef __BIG_ENDIAN__
		assert_int_equal(mImageGetPixelRaw(&image, 0, i), (i * 4) << 8 | (i * 4 + 1));
#else
		assert_int_equal(mImageGetPixelRaw(&image, 0, i), (i * 4 + 1) << 8 | (i * 4));
#endif
	}

	image.depth = 3;
	image.stride = 1;
	image.height = 4;
	image.format = mCOLOR_RGB8;

	for (i = 0; i < 4; ++i) {
#ifdef __BIG_ENDIAN__
		assert_int_equal(mImageGetPixelRaw(&image, 0, i), (i * 3) << 16 | (i * 3 + 1) << 8 | (i * 3 + 2));
#else
		assert_int_equal(mImageGetPixelRaw(&image, 0, i), (i * 3 + 2) << 16 | (i * 3 + 1) << 8 | (i * 3));
#endif
	}

	image.depth = 3;
	image.stride = 2;
	image.height = 2;
	image.format = mCOLOR_RGB8;

	for (i = 0; i < 2; ++i) {
#ifdef __BIG_ENDIAN__
		assert_int_equal(mImageGetPixelRaw(&image, 0, i), (i * 6) << 16 | (i * 6 + 1) << 8 | (i * 6 + 2));
#else
		assert_int_equal(mImageGetPixelRaw(&image, 0, i), (i * 6 + 2) << 16 | (i * 6 + 1) << 8 | (i * 6));
#endif
	}

	image.depth = 4;
	image.stride = 1;
	image.height = 3;
	image.format = mCOLOR_ARGB8;

	for (i = 0; i < 3; ++i) {
#ifdef __BIG_ENDIAN__
		assert_int_equal(mImageGetPixelRaw(&image, 0, i), (i * 4) << 24 | (i * 4 + 1) << 16 | (i * 4 + 2) << 8 | (i * 4 + 3));
#else
		assert_int_equal(mImageGetPixelRaw(&image, 0, i), (i * 4 + 3) << 24 | (i * 4 + 2) << 16 | (i * 4 + 1) << 8 | (i * 4));
#endif
	}
}

M_TEST_DEFINE(oobRead) {
	static uint8_t buffer[8] = {
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
	};

	struct mImage image = {
		.data = buffer,
		.width = 1,
		.height = 1,
		.stride = 1
	};

	image.depth = 1;
	image.format = mCOLOR_L8;

	assert_int_equal(mImageGetPixelRaw(&image, 0, 0), 0xFF);
	assert_int_equal(mImageGetPixelRaw(&image, 1, 0), 0);
	assert_int_equal(mImageGetPixelRaw(&image, 0, 1), 0);
	assert_int_equal(mImageGetPixelRaw(&image, 1, 1), 0);

	image.depth = 2;
	image.format = mCOLOR_RGB5;

	assert_int_equal(mImageGetPixelRaw(&image, 0, 0), 0xFFFF);
	assert_int_equal(mImageGetPixelRaw(&image, 1, 0), 0);
	assert_int_equal(mImageGetPixelRaw(&image, 0, 1), 0);
	assert_int_equal(mImageGetPixelRaw(&image, 1, 1), 0);

	image.depth = 3;
	image.format = mCOLOR_RGB8;

	assert_int_equal(mImageGetPixelRaw(&image, 0, 0), 0xFFFFFF);
	assert_int_equal(mImageGetPixelRaw(&image, 1, 0), 0);
	assert_int_equal(mImageGetPixelRaw(&image, 0, 1), 0);
	assert_int_equal(mImageGetPixelRaw(&image, 1, 1), 0);

	image.depth = 4;
	image.format = mCOLOR_ARGB8;

	assert_int_equal(mImageGetPixelRaw(&image, 0, 0), 0xFFFFFFFF);
	assert_int_equal(mImageGetPixelRaw(&image, 1, 0), 0);
	assert_int_equal(mImageGetPixelRaw(&image, 0, 1), 0);
	assert_int_equal(mImageGetPixelRaw(&image, 1, 1), 0);
}

M_TEST_DEFINE(pitchWrite) {
	static const uint8_t baseline[12] = {
		0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xA, 0xB
	};

	uint8_t buffer[12];

	struct mImage image = {
		.data = buffer,
		.height = 1
	};
	int i;

	image.depth = 1;
	image.width = 12;
	image.format = mCOLOR_L8;

	memset(buffer, 0, sizeof(buffer));
	for (i = 0; i < 12; ++i) {
		mImageSetPixelRaw(&image, i, 0, i);
	}
	assert_memory_equal(baseline, buffer, sizeof(baseline));

	image.depth = 2;
	image.width = 6;
	image.format = mCOLOR_RGB5;

	memset(buffer, 0, sizeof(buffer));
	for (i = 0; i < 6; ++i) {
#ifdef __BIG_ENDIAN__
		mImageSetPixelRaw(&image, i, 0, (i * 2) << 8 | (i * 2 + 1));
#else
		mImageSetPixelRaw(&image, i, 0, (i * 2 + 1) << 8 | (i * 2));
#endif
	}
	assert_memory_equal(baseline, buffer, sizeof(baseline));

	image.depth = 3;
	image.width = 4;
	image.format = mCOLOR_RGB8;

	memset(buffer, 0, sizeof(buffer));
	for (i = 0; i < 4; ++i) {
#ifdef __BIG_ENDIAN__
		mImageSetPixelRaw(&image, i, 0, (i * 3) << 16 | (i * 3 + 1) << 8 | (i * 3 + 2));
#else
		mImageSetPixelRaw(&image, i, 0, (i * 3 + 2) << 16 | (i * 3 + 1) << 8 | (i * 3));
#endif
	}
	assert_memory_equal(baseline, buffer, sizeof(baseline));

	image.depth = 4;
	image.width = 3;
	image.format = mCOLOR_ARGB8;

	memset(buffer, 0, sizeof(buffer));
	for (i = 0; i < 3; ++i) {
#ifdef __BIG_ENDIAN__
		mImageSetPixelRaw(&image, i, 0, (i * 4) << 24 | (i * 4 + 1) << 16 | (i * 4 + 2) << 8 | (i * 4 + 3));
#else
		mImageSetPixelRaw(&image, i, 0, (i * 4 + 3) << 24 | (i * 4 + 2) << 16 | (i * 4 + 1) << 8 | (i * 4));
#endif
	}
	assert_memory_equal(baseline, buffer, sizeof(baseline));
}

M_TEST_DEFINE(strideWrite) {
	static const uint8_t baseline[12] = {
		0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xA, 0xB
	};
	static const uint8_t baseline2x1[12] = {
		0x0, 0x0, 0x2, 0x0, 0x4, 0x0, 0x6, 0x0, 0x8, 0x0, 0xA, 0x0
	};
	static const uint8_t baseline2x2[12] = {
		0x0, 0x1, 0x0, 0x0, 0x4, 0x5, 0x0, 0x0, 0x8, 0x9, 0x0, 0x0
	};
	static const uint8_t baseline3x2[12] = {
		0x0, 0x1, 0x2, 0x0, 0x0, 0x0, 0x6, 0x7, 0x8, 0x0, 0x0, 0x0
	};

	uint8_t buffer[12];

	struct mImage image = {
		.data = buffer,
		.width = 1
	};
	int i;

	image.depth = 1;
	image.stride = 1;
	image.height = 12;
	image.format = mCOLOR_L8;

	memset(buffer, 0, sizeof(buffer));
	for (i = 0; i < 12; ++i) {
		mImageSetPixelRaw(&image, 0, i, i);
	}
	assert_memory_equal(baseline, buffer, sizeof(buffer));

	image.depth = 1;
	image.stride = 2;
	image.height = 6;
	image.format = mCOLOR_L8;

	memset(buffer, 0, sizeof(buffer));
	for (i = 0; i < 6; ++i) {
		mImageSetPixelRaw(&image, 0, i, i * 2);
	}
	assert_memory_equal(baseline2x1, buffer, sizeof(buffer));

	image.depth = 2;
	image.stride = 1;
	image.height = 6;
	image.format = mCOLOR_RGB5;

	memset(buffer, 0, sizeof(buffer));
	for (i = 0; i < 6; ++i) {
#ifdef __BIG_ENDIAN__
		mImageSetPixelRaw(&image, 0, i, (i * 2) << 8 | (i * 2 + 1));
#else
		mImageSetPixelRaw(&image, 0, i, (i * 2 + 1) << 8 | (i * 2));
#endif
	}
	assert_memory_equal(baseline, buffer, sizeof(buffer));

	image.depth = 2;
	image.stride = 2;
	image.height = 3;
	image.format = mCOLOR_RGB5;

	memset(buffer, 0, sizeof(buffer));
	for (i = 0; i < 3; ++i) {
#ifdef __BIG_ENDIAN__
		mImageSetPixelRaw(&image, 0, i, (i * 4) << 8 | (i * 4 + 1));
#else
		mImageSetPixelRaw(&image, 0, i, (i * 4 + 1) << 8 | (i * 4));
#endif
	}
	assert_memory_equal(baseline2x2, buffer, sizeof(buffer));

	image.depth = 3;
	image.stride = 1;
	image.height = 4;
	image.format = mCOLOR_RGB8;

	memset(buffer, 0, sizeof(buffer));
	for (i = 0; i < 4; ++i) {
#ifdef __BIG_ENDIAN__
		mImageSetPixelRaw(&image, 0, i, (i * 3) << 16 | (i * 3 + 1) << 8 | (i * 3 + 2));
#else
		mImageSetPixelRaw(&image, 0, i, (i * 3 + 2) << 16 | (i * 3 + 1) << 8 | (i * 3));
#endif
	}
	assert_memory_equal(baseline, buffer, sizeof(buffer));

	image.depth = 3;
	image.stride = 2;
	image.height = 2;
	image.format = mCOLOR_RGB8;

	memset(buffer, 0, sizeof(buffer));
	for (i = 0; i < 2; ++i) {
#ifdef __BIG_ENDIAN__
		mImageSetPixelRaw(&image, 0, i, (i * 6) << 16 | (i * 6 + 1) << 8 | (i * 6 + 2));
#else
		mImageSetPixelRaw(&image, 0, i, (i * 6 + 2) << 16 | (i * 6 + 1) << 8 | (i * 6));
#endif
	}
	assert_memory_equal(baseline3x2, buffer, sizeof(buffer));

	image.depth = 4;
	image.stride = 1;
	image.height = 3;
	image.format = mCOLOR_ARGB8;

	memset(buffer, 0, sizeof(buffer));
	for (i = 0; i < 3; ++i) {
#ifdef __BIG_ENDIAN__
		mImageSetPixelRaw(&image, 0, i, (i * 4) << 24 | (i * 4 + 1) << 16 | (i * 4 + 2) << 8 | (i * 4 + 3));
#else
		mImageSetPixelRaw(&image, 0, i, (i * 4 + 3) << 24 | (i * 4 + 2) << 16 | (i * 4 + 1) << 8 | (i * 4));
#endif
	}
	assert_memory_equal(baseline, buffer, sizeof(buffer));
}

M_TEST_DEFINE(oobWrite) {
	static uint8_t buffer[8];

	struct mImage image = {
		.data = buffer,
		.width = 1,
		.height = 1,
		.stride = 1
	};

	image.depth = 1;
	image.format = mCOLOR_L8;

	memset(buffer, 0, sizeof(buffer));
	mImageSetPixelRaw(&image, 0, 0, 0xFF);
	mImageSetPixelRaw(&image, 1, 0, 0);
	mImageSetPixelRaw(&image, 0, 1, 0);
	mImageSetPixelRaw(&image, 1, 1, 0);
	assert_memory_equal(buffer, (&(uint8_t[8]) { 0xFF }), sizeof(buffer));

	image.depth = 2;
	image.format = mCOLOR_RGB5;

	memset(buffer, 0, sizeof(buffer));
	mImageSetPixelRaw(&image, 0, 0, 0xFFFF);
	mImageSetPixelRaw(&image, 1, 0, 0);
	mImageSetPixelRaw(&image, 0, 1, 0);
	mImageSetPixelRaw(&image, 1, 1, 0);
	assert_memory_equal(buffer, (&(uint8_t[8]) { 0xFF, 0xFF }), sizeof(buffer));

	image.depth = 3;
	image.format = mCOLOR_RGB8;

	memset(buffer, 0, sizeof(buffer));
	mImageSetPixelRaw(&image, 0, 0, 0xFFFFFF);
	mImageSetPixelRaw(&image, 1, 0, 0);
	mImageSetPixelRaw(&image, 0, 1, 0);
	mImageSetPixelRaw(&image, 1, 1, 0);
	assert_memory_equal(buffer, (&(uint8_t[8]) { 0xFF, 0xFF, 0xFF }), sizeof(buffer));

	image.depth = 4;
	image.format = mCOLOR_ARGB8;

	memset(buffer, 0, sizeof(buffer));
	mImageSetPixelRaw(&image, 0, 0, 0xFFFFFFFF);
	mImageSetPixelRaw(&image, 1, 0, 0);
	mImageSetPixelRaw(&image, 0, 1, 0);
	mImageSetPixelRaw(&image, 1, 1, 0);
	assert_memory_equal(buffer, (&(uint8_t[8]) { 0xFF, 0xFF, 0xFF, 0xFF }), sizeof(buffer));
}

M_TEST_SUITE_DEFINE(Image,
	cmocka_unit_test(pitchRead),
	cmocka_unit_test(strideRead),
	cmocka_unit_test(oobRead),
	cmocka_unit_test(pitchWrite),
	cmocka_unit_test(strideWrite),
	cmocka_unit_test(oobWrite),
)
