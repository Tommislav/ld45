enum Fnt {
	Blank = 0,
	Face = 1,
	FaceInv = 2,
	Heart = 3,
	Diamond = 4,
	Clubs = 5,
	Spades = 6,
	Dot = 7,
	DotInv = 8,
	Circle = 9,
	CircleInv = 10,
	Male = 11,
	Female = 12,
	Note = 13,
	Note2 = 14,
	Sun = 15,
	ArrRight = 16,
	ArrLeft = 17,
	ArrUpDown = 18,
	DoubleExclamations = 19,
	Pi = 20,
	Paragraph = 21,

	Exclamation = 33,
	Quote = 34,
	Hash = 35,
	Dollar = 36,
	Percent = 37,
	Ampersand = 38,
	RightTick = 39,
	ParanStart = 40,
	ParanEnd = 41,
	Mult = 42,
	Plus = 43,
	Comma = 44,
	Dash = 45,
	Punctuation = 46,
	Slash = 47,
	N0 = 48,
	N1 = 49,
	N2 = 50,
	N3 = 51,
	N4 = 52,
	N5 = 53,
	N6 = 54,
	N7 = 55,
	N8 = 56,
	N9 = 57,
	Colon = 58,
	SemiColon = 59,
	Lt = 60,
	Eq = 61,
	Gt = 62,
	QuestionMark = 63,
	At = 64,
	A = 65,
	B = 66,
	C = 67,
	D = 68,
	E = 69,
	F = 70,
	G = 71,
	H = 72,
	I = 73,
	J = 74,
	K = 75,
	L = 76,
	M = 77,
	N = 78,
	O = 79,
	P = 80,
	Q = 81,
	R = 82,
	S = 83,
	T = 84,
	U = 85,
	V = 86,
	W = 87,
	X = 88,
	Y = 89,
	Z = 90,
	SqrBracketStart = 91,
	Backslash = 92,
	SqrBracketEnd = 93,
	Hat = 94,
	Underscore = 95,
	LeftTick = 96,
	a = 97,
	b = 98,
	c = 99,
	d = 100,
	e = 101,
	f = 102,
	g = 103,
	h = 104,
	i = 105,
	j = 106,
	k = 107,
	l = 108,
	m = 109,
	n = 110,
	o = 111,
	p = 112,
	q = 113,
	r = 114,
	s = 115,
	t = 116,
	u = 117,
	v = 118,
	w = 119,
	x = 120,
	y = 121,
	z = 122,

	Filled = 219,
	Dissolve1 = 178,
	Dissolve2 = 177,
	Dissolve3 = 176,

	Frame1Vert = 179,
	Frame1Horiz = 196,
	Frame1TR = 192,
	Frame1BL = 191,
	Frame1BR = 217,
	Frame1TL = 218,



	Aring = 991,
	Auml = 992,
	Ouml = 993
};



Fnt CharToFnt(const char* c) {
	switch (*c) {
	case ' ':
		return Fnt::Blank;

	case 'A':
		return Fnt::A;
	case 'a':
		return Fnt::a;
	case 'B':
		return Fnt::B;
	case 'b':
		return Fnt::b;
	case 'C':
		return Fnt::C;
	case 'c':
		return Fnt::c;
	case 'D':
		return Fnt::D;
	case 'd':
		return Fnt::d;
	case 'E':
		return Fnt::E;
	case 'e':
		return Fnt::e;
	case 'F':
		return Fnt::F;
	case 'f':
		return Fnt::f;
	case 'G':
		return Fnt::G;
	case 'g':
		return Fnt::g;
	case 'H':
		return Fnt::H;
	case 'h':
		return Fnt::h;
	case 'I':
		return Fnt::I;
	case 'i':
		return Fnt::i;
	case 'J':
		return Fnt::J;
	case 'j':
		return Fnt::j;
	case 'K':
		return Fnt::K;
	case 'k':
		return Fnt::k;
	case 'L':
		return Fnt::L;
	case 'l':
		return Fnt::l;
	case 'M':
		return Fnt::M;
	case 'm':
		return Fnt::m;
	case 'N':
		return Fnt::N;
	case 'n':
		return Fnt::n;
	case 'O':
		return Fnt::O;
	case 'o':
		return Fnt::o;
	case 'P':
		return Fnt::P;
	case 'p':
		return Fnt::p;
	case 'Q':
		return Fnt::Q;
	case 'q':
		return Fnt::q;
	case 'R':
		return Fnt::R;
	case 'r':
		return Fnt::r;
	case 'S':
		return Fnt::S;
	case 's':
		return Fnt::s;
	case 'T':
		return Fnt::T;
	case 't':
		return Fnt::t;
	case 'U':
		return Fnt::U;
	case 'u':
		return Fnt::u;
	case 'V':
		return Fnt::V;
	case 'v':
		return Fnt::v;
	case 'W':
		return Fnt::W;
	case 'w':
		return Fnt::w;
	case 'X':
		return Fnt::X;
	case 'x':
		return Fnt::x;
	case 'Y':
		return Fnt::Y;
	case 'y':
		return Fnt::y;
	case 'Z':
		return Fnt::Z;
	case 'z':
		return Fnt::z;

	case '.':
		return Fnt::Punctuation;
	case ',':
		return Fnt::Comma;
	case '!':
		return Fnt::Exclamation;
	case '?':
		return Fnt::QuestionMark;
	case '(':
		return Fnt::ParanStart;
	case ')':
		return Fnt::ParanEnd;
	case '<':
		return Fnt::Lt;
	case '>':
		return Fnt::Gt;


	default:
		return Fnt::Blank;
	}
}
