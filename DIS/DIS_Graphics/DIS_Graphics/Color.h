#ifndef COLOR_H
#define COLOR_H


class Color
{
public:

	Color()
	{
		r=g=b=a = 0.0f;
	}

	Color(float R, float G, float B, float A=1.0f)
	{
		r=R;
		g=G;
		b=B;
		a=A;
	}

	Color(const Color& c2)
	{
		r= c2.r;
		g= c2.g;
		b= c2.b;
		a= c2.a;
	}

	Color(Color* c2)
	{
		r= c2->r;
		g= c2->g;
		b= c2->b;
		a= c2->a;
	}

	Color(int rgba)
	{
		r = getRed(rgba);
		g = getGreen(rgba);
		b = getBlue(rgba);
		a = getAlpha(rgba);
	}

	void operator=(const Color& col)
	{
		r = col.r;
		g = col.g;
		b = col.b;
		a = col.a;
	}

	void operator+=(const Color &col)
	{
		r += col.r;
		g += col.g;
		b += col.b;
		a += col.a;
	}

	void operator-=(const Color &col)
	{
		r -= col.r;
		g -= col.g;
		b -= col.b;
		a -= col.a;
	}

    int makeIntRGB(int R, int G, int B){
        return ((int) (((R) << 16) | ((G) << 8) | (B)));
    }

    int makeIntARGB(int R, int G, int B, int A){
        return ((int) (((A) << 24)| ((R) << 16) | ((G) << 8) | (B)));
    }

	int getRed(int rgb){
        return (((rgb) >> 16) & 0xff);
    }
    
	int getGreen(int rgb){
        return (((rgb) >> 8) & 0xff);
    }
    
    int getBlue(int rgb){
        return ((rgb) & 0xff);
    } 

	int getAlpha(int rgba) {
		return (((rgba) >> 24) & 0xff);
	}

	int getIntRGBA()
	{
		return ((int) ((int(a) << 24) | (int(r) << 16) | (int(g) << 8) | int(b)));
	}

	int getIntRGB()
	{
		return ((int) ((int(r) << 16) | (int(g) << 8) | int(b)));
	}

	float r;
	float g;
	float b;
	float a;
};

inline
Color operator+(const Color &c1, const Color &c2)
{
	return Color(c1.r + c2.r, c1.g + c2.g, c1.b + c2.b, c1.a + c2.a);
}

inline
Color operator-(const Color &c1, const Color &c2)
{
	return Color(c1.r - c2.r, c1.g - c2.g, c1.b - c2.b, c1.a - c2.a);
}

#endif