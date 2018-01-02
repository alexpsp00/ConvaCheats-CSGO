namespace ValveSDK
{
	enum OverrideType_t
	{
		OVERRIDE_NORMAL = 0,
		OVERRIDE_BUILD_SHADOWS,
		OVERRIDE_DEPTH_WRITE,
		OVERRIDE_WHATEVER
	};

	struct DrawModelState_t
	{
		studiohdr_t*			m_pStudioHdr;
		PVOID					m_pStudioHWData;
		PVOID					m_pRenderable;
		const matrix3x4_t		*m_pModelToWorld;
		int						m_decals;
		int						m_drawFlags;
		int						m_lod;
	};

	enum MaterialVarFlags_t
	{
		MATERIAL_VAR_DEBUG = (1 << 0),
		MATERIAL_VAR_NO_DEBUG_OVERRIDE = (1 << 1),
		MATERIAL_VAR_NO_DRAW = (1 << 2),
		MATERIAL_VAR_USE_IN_FILLRATE_MODE = (1 << 3),

		MATERIAL_VAR_VERTEXCOLOR = (1 << 4),
		MATERIAL_VAR_VERTEXALPHA = (1 << 5),
		MATERIAL_VAR_SELFILLUM = (1 << 6),
		MATERIAL_VAR_ADDITIVE = (1 << 7),
		MATERIAL_VAR_ALPHATEST = (1 << 8),
		MATERIAL_VAR_MULTIPASS = (1 << 9),
		MATERIAL_VAR_ZNEARER = (1 << 10),
		MATERIAL_VAR_MODEL = (1 << 11),
		MATERIAL_VAR_FLAT = (1 << 12),
		MATERIAL_VAR_NOCULL = (1 << 13),
		MATERIAL_VAR_NOFOG = (1 << 14),
		MATERIAL_VAR_IGNOREZ = (1 << 15),
		MATERIAL_VAR_DECAL = (1 << 16),
		MATERIAL_VAR_ENVMAPSPHERE = (1 << 17),
		MATERIAL_VAR_NOALPHAMOD = (1 << 18),
		MATERIAL_VAR_ENVMAPCAMERASPACE = (1 << 19),
		MATERIAL_VAR_BASEALPHAENVMAPMASK = (1 << 20),
		MATERIAL_VAR_TRANSLUCENT = (1 << 21),
		MATERIAL_VAR_NORMALMAPALPHAENVMAPMASK = (1 << 22),
		MATERIAL_VAR_NEEDS_SOFTWARE_SKINNING = (1 << 23),
		MATERIAL_VAR_OPAQUETEXTURE = (1 << 24),
		MATERIAL_VAR_ENVMAPMODE = (1 << 25),
		MATERIAL_VAR_SUPPRESS_DECALS = (1 << 26),
		MATERIAL_VAR_HALFLAMBERT = (1 << 27),
		MATERIAL_VAR_WIREFRAME = (1 << 28),
		MATERIAL_VAR_ALLOWALPHATOCOVERAGE = (1 << 29),

		// NOTE: Only add flags here that either should be read from
		// .vmts or can be set directly from client code. Other, internal
		// flags should to into the flag enum in IMaterialInternal.h
	};

	class IMaterial
	{
	public:
		virtual int vfunc00() = 0;
		virtual int vfunc01() = 0;
		virtual int vfunc02() = 0;
		virtual int vfunc03() = 0;
		virtual int vfunc04() = 0;
		virtual int vfunc05() = 0;
		virtual int vfunc06() = 0;
		virtual int vfunc07() = 0;
		virtual int vfunc08() = 0;
		virtual int vfunc09() = 0;
		virtual int vfunc10() = 0;
		virtual int vfunc11() = 0;
		virtual void IncrementReferenceCount(void) = 0;
		virtual int vfunc13() = 0;
		virtual int vfunc14() = 0;
		virtual int vfunc15() = 0;
		virtual int vfunc16() = 0;
		virtual int vfunc17() = 0;
		virtual int vfunc18() = 0;
		virtual int vfunc19() = 0;
		virtual int vfunc20() = 0;
		virtual int vfunc21() = 0;
		virtual int vfunc22() = 0;
		virtual int vfunc23() = 0;
		virtual int vfunc24() = 0;
		virtual int vfunc25() = 0;
		virtual int vfunc26() = 0;
		virtual void AlphaModulate(float alpha) = 0;
		virtual void ColorModulate(float r, float g, float b) = 0;

		virtual void SetMaterialVarFlag(MaterialVarFlags_t flag, bool on) = 0;
		virtual bool GetMaterialVarFlag(MaterialVarFlags_t flag) const = 0;

		virtual int vfunc31() = 0;
		virtual int vfunc32() = 0;
		virtual int vfunc33() = 0;
		virtual int vfunc34() = 0;
		virtual int vfunc35() = 0;
		virtual int vfunc36() = 0;
		virtual int vfunc37() = 0;
		virtual int vfunc38() = 0;
		virtual int vfunc39() = 0;
		virtual int vfunc40() = 0;
		virtual int vfunc41() = 0;
		virtual bool IsErrorMaterial() = 0;
		virtual int vfunc43() = 0;
		virtual float GetAlphaModulation() = 0;
		virtual void GetColorModulation(float *r, float *g, float *b) = 0;
	};

	class Color
	{
	public:
		// constructors
		Color()
		{
			*((int *)this) = 0;
		}
		Color(int color32)
		{
			*((int *)this) = color32;
		}
		Color(int _r, int _g, int _b)
		{
			SetColor(_r, _g, _b, 255);
		}
		Color(int _r, int _g, int _b, int _a)
		{
			SetColor(_r, _g, _b, _a);
		}

		// set the color
		// r - red component (0-255)
		// g - green component (0-255)
		// b - blue component (0-255)
		// a - alpha component, controls transparency (0 - transparent, 255 - opaque);
		void SetColor(int _r, int _g, int _b, int _a = 255)
		{
			_color[0] = (unsigned char)_r;
			_color[1] = (unsigned char)_g;
			_color[2] = (unsigned char)_b;
			_color[3] = (unsigned char)_a;
		}

		void GetColor(int &_r, int &_g, int &_b, int &_a) const
		{
			_r = _color[0];
			_g = _color[1];
			_b = _color[2];
			_a = _color[3];
		}

		void SetRawColor(int color32)
		{
			*((int*)this) = color32;
		}

		int GetRawColor() const
		{
			return *((int*)this);
		}

		int GetD3DColor() const
		{
			return ((int)((((_color[3]) & 0xff) << 24) | (((_color[0]) & 0xff) << 16) | (((_color[1]) & 0xff) << 8) | ((_color[2]) & 0xff)));
		}

		inline int r() const	{ return _color[0]; }
		inline int g() const	{ return _color[1]; }
		inline int b() const	{ return _color[2]; }
		inline int a() const	{ return _color[3]; }

		unsigned char &operator[](int index)
		{
			return _color[index];
		}

		const unsigned char &operator[](int index) const
		{
			return _color[index];
		}

		bool operator == (const Color &rhs) const
		{
			return (*((int *)this) == *((int *)&rhs));
		}

		bool operator != (const Color &rhs) const
		{
			return !(operator==(rhs));
		}

		Color &operator=(const Color &rhs)
		{
			SetRawColor(rhs.GetRawColor());
			return *this;
		}

		Color &operator=(const color32 &rhs)
		{
			_color[0] = rhs.r;
			_color[1] = rhs.g;
			_color[2] = rhs.b;
			_color[3] = rhs.a;
			return *this;
		}

		color32 ToColor32() const
		{
			color32 newColor;
			newColor.r = _color[0];
			newColor.g = _color[1];
			newColor.b = _color[2];
			newColor.a = _color[3];
			return newColor;
		}

		float* Base()
		{
			float clr[3];

			clr[0] = _color[0] / 255.0f;
			clr[1] = _color[1] / 255.0f;
			clr[2] = _color[2] / 255.0f;

			return &clr[0];
		}

		float Hue() const
		{
			if (_color[0] == _color[1] && _color[1] == _color[2])
			{
				return 0.0f;
			}

			float r = _color[0] / 255.0f;
			float g = _color[1] / 255.0f;
			float b = _color[2] / 255.0f;

			float max = r > g ? r : g > b ? g : b,
				min = r < g ? r : g < b ? g : b;
			float delta = max - min;
			float hue = 0.0f;

			if (r == max)
			{
				hue = (g - b) / delta;
			}
			else if (g == max)
			{
				hue = 2 + (b - r) / delta;
			}
			else if (b == max)
			{
				hue = 4 + (r - g) / delta;
			}
			hue *= 60;

			if (hue < 0.0f)
			{
				hue += 360.0f;
			}
			return hue;
		}

		float Saturation() const
		{
			float r = _color[0] / 255.0f;
			float g = _color[1] / 255.0f;
			float b = _color[2] / 255.0f;

			float max = r > g ? r : g > b ? g : b,
				min = r < g ? r : g < b ? g : b;
			float l, s = 0;

			if (max != min)
			{
				l = (max + min) / 2;
				if (l <= 0.5f)
					s = (max - min) / (max + min);
				else
					s = (max - min) / (2 - max - min);
			}
			return s;
		}

		float Brightness() const
		{
			float r = _color[0] / 255.0f;
			float g = _color[1] / 255.0f;
			float b = _color[2] / 255.0f;

			float max = r > g ? r : g > b ? g : b,
				min = r < g ? r : g < b ? g : b;
			return (max + min) / 2;
		}

		Color FromHSB(float hue, float saturation, float brightness)
		{
			float h = hue == 1.0f ? 0 : hue * 6.0f;
			float f = h - (int)h;
			float p = brightness * (1.0f - saturation);
			float q = brightness * (1.0f - saturation * f);
			float t = brightness * (1.0f - (saturation * (1.0f - f)));

			if (h < 1)
			{
				return Color(
					(unsigned char)(brightness * 255),
					(unsigned char)(t * 255),
					(unsigned char)(p * 255)
					);
			}
			else if (h < 2)
			{
				return Color(
					(unsigned char)(q * 255),
					(unsigned char)(brightness * 255),
					(unsigned char)(p * 255)
					);
			}
			else if (h < 3)
			{
				return Color(
					(unsigned char)(p * 255),
					(unsigned char)(brightness * 255),
					(unsigned char)(t * 255)
					);
			}
			else if (h < 4)
			{
				return Color(
					(unsigned char)(p * 255),
					(unsigned char)(q * 255),
					(unsigned char)(brightness * 255)
					);
			}
			else if (h < 5)
			{
				return Color(
					(unsigned char)(t * 255),
					(unsigned char)(p * 255),
					(unsigned char)(brightness * 255)
					);
			}
			else
			{
				return Color(
					(unsigned char)(brightness * 255),
					(unsigned char)(p * 255),
					(unsigned char)(q * 255)
					);
			}
		}

		static Color Red()		{ return Color(255, 0, 0); }
		static Color Green()	{ return Color(0, 255, 0); }
		static Color Blue()		{ return Color(0, 0, 255); }
		static Color LightBlue(){ return Color(50, 160, 255); }
		static Color Grey()		{ return Color(128, 128, 128); }
		static Color DarkGrey()	{ return Color(45, 45, 45); }
		static Color Black()	{ return Color(0, 0, 0); }
		static Color White()	{ return Color(255, 255, 255); }
		static Color Purple()	{ return Color(220, 0, 220); }

	private:
		unsigned char _color[4];
	};

	typedef unsigned short MaterialHandle_t;

	class IMaterialSystem
	{
	public:
		IMaterial *CreateMaterial(const char *pMaterialName, PVOID pVMTKeyValues)
		{
			typedef IMaterial*(__thiscall* OriginalFn)(PVOID, const char*, PVOID);
			return getvfunc<OriginalFn>(this, 82)(this, pMaterialName, pVMTKeyValues);
		}
	};

	class IVModelRender
	{
	public:
		virtual int		vfunc00() = 0;
		virtual void	ForcedMaterialOverride(IMaterial *newMaterial, OverrideType_t nOverrideType = OVERRIDE_NORMAL) = 0;
		virtual bool	vfunc02() = 0;
		virtual int		vfunc03() = 0;
		virtual int		vfunc04() = 0;
		virtual int		vfunc05() = 0;
		virtual int		vfunc06() = 0;
		virtual int		vfunc07() = 0;
		virtual int		vfunc08() = 0;
		virtual int		vfunc09() = 0;
		virtual int		vfunc10() = 0;
		virtual int		vfunc11() = 0;
		virtual int		vfunc12() = 0;
		virtual int		vfunc13() = 0;
		virtual int		vfunc14() = 0;
		virtual int		vfunc15() = 0;
		virtual int		vfunc16() = 0;
		virtual int		vfunc17() = 0;
		virtual int		vfunc18() = 0;
		virtual void DrawModelExecute(const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld = NULL) = 0;
	};

	class IVRenderView
	{
	public:

		virtual void vfunc00() = 0;
		virtual void vfunc01() = 0;
		virtual void vfunc02() = 0;
		virtual void vfunc03() = 0;

		virtual void SetBlend(float blend) = 0;
		virtual float GetBlend(void) = 0;

		virtual void SetColorModulation(float const* blend) = 0;
		virtual void GetColorModulation(float* blend) = 0;
	};

	class ISurface
	{
	public:
		void DrawSetColor(int r, int g, int b, int a)
		{
			typedef void(__thiscall* OriginalFn)(PVOID, int, int, int, int); // 
			getvfunc<OriginalFn>(this, 15)(this, r, g, b, a); // r, g, b, a
		}

		void DrawSetColor1(Color color)
		{
			typedef void(__thiscall* OriginalFn)(PVOID, Color); // int, int , int, int
			getvfunc<OriginalFn>(this, 15)(this, color); // r, g, b, a
		}

		void DrawFilledRect(int x0, int y0, int x1, int y1)
		{
			typedef void(__thiscall* OriginalFn)(PVOID, int, int, int, int);
			getvfunc<OriginalFn>(this, 16)(this, x0, y0, x1, y1);
		}

		void DrawSetTextFont(unsigned long font)
		{
			typedef void(__thiscall* OriginalFn)(PVOID, unsigned long);
			getvfunc<OriginalFn>(this, 23)(this, font);
		}

		void DrawLine(int x0, int y0, int x1, int y1)
		{
			typedef void(__thiscall* OriginalFn)(PVOID, int, int, int, int);
			getvfunc<OriginalFn>(this, 19)(this, x0, y0, x1, y1);
		}

		void DrawSetTextColor(int r, int g, int b, int a)
		{
			typedef void(__thiscall* OriginalFn)(PVOID, int, int, int, int);
			getvfunc<OriginalFn>(this, 25)(this, r, g, b, a);
		}

		void DrawSetTextPos(int x, int y)
		{
			typedef void(__thiscall* OriginalFn)(PVOID, int, int);
			getvfunc<OriginalFn>(this, 26)(this, x, y);
		}

		void DrawPrintText(const wchar_t *text, int textLen)
		{
			typedef void(__thiscall* OriginalFn)(PVOID, const wchar_t *, int, int);
			return getvfunc<OriginalFn>(this, 28)(this, text, textLen, 0);
		}

		unsigned long CreateFont()
		{
			typedef unsigned int(__thiscall* OriginalFn)(PVOID);
			return getvfunc<OriginalFn>(this, 71)(this);
		}

		void SetFontGlyphSet(unsigned long &font, const char *windowsFontName, int tall, int weight, int blur, int scanlines, int flags)
		{
			typedef void(__thiscall* OriginalFn)(PVOID, unsigned long, const char*, int, int, int, int, int, int, int);
			getvfunc<OriginalFn>(this, 72)(this, font, windowsFontName, tall, weight, blur, scanlines, flags, 0, 0);
		}

		void GetTextSize(unsigned long font, const wchar_t *text, int &wide, int &tall)
		{
			typedef void(__thiscall* OriginalFn)(void*, unsigned long font, const wchar_t *text, int &wide, int &tall);
			getvfunc<OriginalFn>(this, 79)(this, font, text, wide, tall);
		}

		void DrawColoredCircle(int centerx, int centery, float radius, int r, int g, int b, int a)
		{
			typedef void(__thiscall* OriginalFn)(void*, int, int, float, int, int, int, int);
			getvfunc<OriginalFn>(this, 162)(this, centerx, centery, radius, r, g, b, a);
		}

		void LockCursor()
		{
			typedef void(__thiscall* OriginalFn)(void*);
			getvfunc<OriginalFn>(this, 67)(this);
		}
	};
}