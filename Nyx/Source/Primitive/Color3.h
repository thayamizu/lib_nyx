/********************************************************************************
*
*  The MIT License
*
* Copyright (c)2010 -  t.hayamizu
*
*�ȉ��ɒ�߂�����ɏ]���A�{�\�t�g�E�F�A����ъ֘A�����̃t�@�C���i�ȉ��u�\�t�g�E�F�A�v�j�̕������擾���邷�ׂĂ̐l�ɑ΂��A�\�t�g�E�F
*�A�𖳐����Ɉ������Ƃ𖳏��ŋ����܂��B����ɂ́A�\�t�g�E�F�A�̕������g�p�A���ʁA�ύX�A�����A�f�ځA�Еz�A�T�u���C�Z���X�A�����/��
*���͔̔����錠���A����у\�t�g�E�F�A��񋟂��鑊��ɓ������Ƃ������錠�����������Ɋ܂܂�܂��B
*
*��L�̒��쌠�\������і{�����\�����A�\�t�g�E�F�A�̂��ׂĂ̕����܂��͏d�v�ȕ����ɋL�ڂ�����̂Ƃ��܂��B
*
*�\�t�g�E�F�A�́u����̂܂܁v�ŁA�����ł��邩�Öقł��邩���킸�A����̕ۏ؂��Ȃ��񋟂���܂��B�����ł����ۏ؂Ƃ́A���i���A����̖�*�I�ւ̓K�����A����ь�����N�Q�ɂ��Ă̕ۏ؂��܂݂܂����A����Ɍ��肳�����̂ł͂���܂���B ��҂܂��͒��쌠�҂́A�_��s�ׁA�s�@
*�s�ׁA�܂��͂���ȊO�ł��낤�ƁA�\�t�g�E�F�A�ɋN���܂��͊֘A���A���邢�̓\�t�g�E�F�A�̎g�p�܂��͂��̑��̈����ɂ���Đ������؂̐�
*���A���Q�A���̑��̋`���ɂ��ĉ���̐ӔC������Ȃ����̂Ƃ��܂��B 
********************************************************************************/
#ifndef NYX_CORE_INCLUDED_COLOR3_H_
#define NYX_CORE_INCLUDED_COLOR3_H_

namespace Nyx
{
	template <typename T>
	class Color3{
		static_assert(std::is_arithmetic<T>::value, "T required arithmetic type.");
	public:
		//--------------------------------------------------------------------------------------
		// �ϐ�
		//--------------------------------------------------------------------------------------
		union {
			struct {
				///
				T r;
				///
				T g;
				///
				T b;
			};

			T elements[3];
		} ;
		//--------------------------------------------------------------------------------------
		// �萔
		//--------------------------------------------------------------------------------------
		///
		static const Color3<T> White;

		///
		static const Color3<T> Gray;

		///
		static const Color3<T> Black;

		///
		static const Color3<T> Red;

		///
		static const Color3<T> Green;

		///
		static const Color3<T> Blue;

		///
		static const Color3<T> Cyan;

		///
		static const Color3<T> Magenta;

		///
		static const Color3<T> Yellow;

		//--------------------------------------------------------------------------------------
		// �R���X�g���N�^
		//--------------------------------------------------------------------------------------
		Color3<T>() {
			Set(0, 0, 0);
		}
		Color3<T>(T r, T g, T b) {
			Set(r, g, b);
		}
		Color3<T>(const Color3<T>& other) {
			Set(other.r, other.g, other.b);
		}

		void Set(T r, T g, T b) {
			this->r = r;
			this->g = g;
			this->b = b;
			Clamp();

		}
		void Clamp() {
			r = Math::Clamp<T>(r, 0, 255); 
			g = Math::Clamp<T>(g, 0, 255); 
			b = Math::Clamp<T>(b, 0, 255); 
		}

		

		//--------------------------------------------------------------------------------------
		// ���Z
		//--------------------------------------------------------------------------------------
		Color3<T> operator +(const Color3<T>&  color) const {
			return Color3<T>(r + color.r, g + color.g, b + color.b);

		}
		Color3<T> operator -(const Color3<T>&  color) const {
			return Color3<T>(r - color.r, g - color.g, b - color.b);

		}
		Color3<T> operator *(const T value) const {
			return Color3<T>(r * value, g * value, b * value);

		}
		Color3<T> operator /(const T value) const {
			return Color3<T>(r / value, g / value, b / value);

		}

		//--------------------------------------------------------------------------------------
		// ������Z
		//--------------------------------------------------------------------------------------
		Color3<T>& operator +=(const Color3<T>&  color) {
			Set(r + color.r, g + color.g, b + color.b);
			return *this;
		}
		Color3<T>& operator -=(const Color3<T>& color) {
			Set(r - color.r, g - color.g, b - color.b);
			return *this;
		}
		Color3<T>& operator *=(T value) {
			Set(r * value, g * value, b * value);
			return *this;
		}
		Color3<T>& operator /=(T value) {
			Set(r / value, g / value, b / value);
			return *this;
		}

		//--------------------------------------------------------------------------------------
		// �_�����Z
		//--------------------------------------------------------------------------------------
		bool operator ==(const Color3<T>& color) const {
			return (
				Math::Abs(r - color.r) <= Math::Epsilon &&
				Math::Abs(g - color.g) <= Math::Epsilon &&
				Math::Abs(b - color.b) <= Math::Epsilon);
		}
		bool operator !=(const Color3<T>& color) const {
			return !( *this == color);
		}
	};


	//--------------------------------------------------------------------------------------
	// �ʖ���`
	//--------------------------------------------------------------------------------------
	typedef Color3<uchar> Color3c;
	typedef Color3<float> Color3f;

	template<>
	void Color3f::Clamp() {
		r = Math::Clamp<float>(r, 0.f, 1.f); 
		g = Math::Clamp<float>(g, 0.f, 1.f); 
		b = Math::Clamp<float>(b, 0.f, 1.f); 
	}


	//--------------------------------------------------------------------------------------
	// �萔��`
	//--------------------------------------------------------------------------------------
	template <typename T>
	const Color3<T> Color3<T>::White(255 , 255, 255);

	///
	template <typename T>
	const Color3<T> Color3<T>::Gray(128, 128, 128);

	///
	template <typename T>
	const Color3<T> Color3<T>::Black(0, 0, 0);

	///
	template <typename T>
	const Color3<T> Color3<T>::Red(255, 0, 0);

	///
	template <typename T>
	const Color3<T> Color3<T>::Green(0, 255, 0);

	///
	template <typename T>
	const Color3<T> Color3<T>::Blue(0, 0, 255);

	///
	template <typename T>
	const Color3<T> Color3<T>::Cyan(0, 255, 255);

	///
	template <typename T>
	const Color3<T> Color3<T>::Magenta(255, 0, 255);

	///
	template <typename T>
	const Color3<T> Color3<T>::Yellow(255, 255, 0);

	///
	const Color3f Color3f::White(1.f , 1.f, 1.f);

	///
	const Color3f  Color3f::Gray(0.5f, 0.5f, 0.5f);

	///
	const Color3f  Color3f::Black(0.f, 0.f, 0.f);

	///
	const Color3f  Color3f::Red(1.f, 0.f, 0.f);

	///
	const Color3f  Color3f::Green(0, 1.f, 0);

	///
	const Color3f  Color3f::Blue(0, 0, 1.f);

	///
	const Color3f  Color3f::Cyan(0, 1.f, 1.f);

	///
	const Color3f Color3f::Magenta(1.f, 0, 1.f);

	///
	const Color3f  Color3f::Yellow(1.f, 1.f, 0);
}
#endif