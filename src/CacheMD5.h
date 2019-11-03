#ifndef CACHES_CACHEMD5_H
#define CACHES_CACHEMD5_H

#include <cstring>
#include <string>

using std::string;

#define s11 7
#define s12 12
#define s13 17
#define s14 22
#define s21 5
#define s22 9
#define s23 14
#define s24 20
#define s31 4
#define s32 11
#define s33 16
#define s34 23
#define s41 6
#define s42 10
#define s43 15
#define s44 21

#define F(x, y, z) (((x) & (y)) | ((~(x)) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~(z))))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~(z))))

#define ROTATE_LEFT(num, n) (((num) << (n)) | ((num) >> (32 - (n))))

#define FF(a, b, c, d, x, s, ac)                                                                                       \
    {                                                                                                                  \
        (a) += F((b), (c), (d)) + (x) + (ac);                                                                          \
        (a) = ROTATE_LEFT((a), (s));                                                                                   \
        (a) += (b);                                                                                                    \
    }
#define GG(a, b, c, d, x, s, ac)                                                                                       \
    {                                                                                                                  \
        (a) += G((b), (c), (d)) + (x) + (ac);                                                                          \
        (a) = ROTATE_LEFT((a), (s));                                                                                   \
        (a) += (b);                                                                                                    \
    }
#define HH(a, b, c, d, x, s, ac)                                                                                       \
    {                                                                                                                  \
        (a) += H((b), (c), (d)) + (x) + (ac);                                                                          \
        (a) = ROTATE_LEFT((a), (s));                                                                                   \
        (a) += (b);                                                                                                    \
    }
#define II(a, b, c, d, x, s, ac)                                                                                       \
    {                                                                                                                  \
        (a) += I((b), (c), (d)) + (x) + (ac);                                                                          \
        (a) = ROTATE_LEFT((a), (s));                                                                                   \
        (a) += (b);                                                                                                    \
    }

/* Define of un_char.*/
typedef unsigned char un_char;
/* Define of un_int. */
typedef unsigned int un_int;

class MD5 {
public:
    /* Construct a MD5 object with a string. */
    explicit MD5(const string &message);

    /* Generate md5 digest. */
    const un_char *get_digest();

    /* Convert digest to string value */
    string to_str();

private:
    /* Initialization the md5 object, processing another message block,
     * and updating the context.*/
    void init(const un_char *input, size_t len);

    /* MD5 basic transformation. Transforms state based on block. */
    void transform(const un_char block[64]);

    /* Encodes input (unsigned long) into output (un_char). */
    void encode(const un_int *input, un_char *output, size_t length);

    /* Decodes input (un_char) into output (unsigned long). */
    void decode(const un_char *input, un_int *output, size_t length);

private:
    /* Flag for mark whether Calculate finished. */
    bool finished;

    /* state (ABCD). */
    un_int state[4]{0};

    /* number of bits, low-order word first. */
    un_int count[2]{0};

    /* input buffer. */
    un_char buffer[64]{0};

    /* message digest. */
    un_char digest[16]{0};

    /* padding for Calculate. */
    static const un_char PADDING[64];

    /* Hex numbers. */
    static const char HEX_NUMBERS[16];
};

#endif // CACHES_CACHEMD5_H
