/*
 * Made for educational purposes to allow students to play around with tighter and less precise floating point format. (7 bit mantissa, 8 bit exponent)
 */
typedef struct myfloat {
    signed char mantissa;
    signed char exponent;
} myfloat_type;


void doub2myfloat(double arg, myfloat_type *res) {
    int exponent;
    double temp;
    exponent = ceil(log(abs(arg)) / log(2)); //base 2 logarithm
    temp = arg * pow(2, 7 - exponent);
    res->mantissa = (signed char)temp;
    res->exponent = exponent - 7;
}

double myfloat2double(myfloat_type *arg1) {
    double res = (double)(arg1->mantissa) * pow(2, arg1->exponent);
    return res;
}


void add_float(myfloat_type *arg1, myfloat_type *arg2, myfloat_type *result) {
    signed char shift;
    myfloat_type tmpresult;
    int tmp;
    int xxp = 0;

    if (arg1-> exponent > arg2-> exponent) {
        if (arg1->mantissa == 0) {
            result->mantissa = arg2->mantissa;
            result->exponent = arg2-> exponent;
            return;
        }

        shift = arg1-> exponent - arg2-> exponent;
        tmpresult.mantissa = (signed char)(arg2->mantissa / pow(2, shift));

        tmp = (int)(arg1->mantissa + tmpresult.mantissa);

        if (abs(tmp) > 127) {
            tmp /= 2;
            xxp = 1;
        }
        result->mantissa = (signed char) tmp;
        result->exponent = arg1-> exponent + xxp;
    }
    else {
        if (arg2->mantissa == 0) {
            result->mantissa = arg1->mantissa;
            result->exponent = arg1->exponent;
            return;
        }

        shift = arg2-> exponent - arg1-> exponent;

        tmpresult.mantissa = (signed char)(arg1->mantissa / pow(2, shift));
        tmp = (int)(arg2->mantissa + tmpresult.mantissa);
        if (abs(tmp) > 127) {
            tmp /= 2;
            xxp = 1;
        }
        result->mantissa = (signed char) tmp;
        result->exponent = arg2-> exponent + xxp;
    }
}

void mult_float(myfloat_type *arg1, myfloat_type *arg2, myfloat_type *result) {
    int temp;
    signed char sign = 1;

    char i = 0;
    temp = (int)(arg1-> mantissa) * (int)(arg2-> mantissa);

    if (temp < 0)
        sign = -1;

    temp = abs(temp);
    while (abs(temp) >= 128) {
        i++;
        temp = temp >> 1;
    }
    result->mantissa = (unsigned char) temp;
    if (result->mantissa < 0)
        result->mantissa = (signed char)(-1.0) * result->mantissa;

    result->mantissa = result->mantissa * sign; //add recorded sign
    result->exponent = arg1->exponent + arg2->exponent + i;
}
