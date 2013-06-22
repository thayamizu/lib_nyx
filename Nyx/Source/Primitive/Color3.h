/********************************************************************************
*
*  The MIT License
*
* Copyright (c)2010 -  t.hayamizu
*
*以下に定める条件に従い、本ソフトウェアおよび関連文書のファイル（以下「ソフトウェア」）の複製を取得するすべての人に対し、ソフトウェ
*アを無制限に扱うことを無償で許可します。これには、ソフトウェアの複製を使用、複写、変更、結合、掲載、頒布、サブライセンス、および/ま
*たは販売する権利、およびソフトウェアを提供する相手に同じことを許可する権利も無制限に含まれます。
*
*上記の著作権表示および本許諾表示を、ソフトウェアのすべての複製または重要な部分に記載するものとします。
*
*ソフトウェアは「現状のまま」で、明示であるか暗黙であるかを問わず、何らの保証もなく提供されます。ここでいう保証とは、商品性、特定の目*的への適合性、および権利非侵害についての保証も含みますが、それに限定されるものではありません。 作者または著作権者は、契約行為、不法
*行為、またはそれ以外であろうと、ソフトウェアに起因または関連し、あるいはソフトウェアの使用またはその他の扱いによって生じる一切の請
*求、損害、その他の義務について何らの責任も負わないものとします。 
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
		// 変数
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
		// 定数
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
		// コンストラクタ
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
		// 演算
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
		// 代入演算
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
		// 論理演算
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
	// 別名定義
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
	// 定数定義
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