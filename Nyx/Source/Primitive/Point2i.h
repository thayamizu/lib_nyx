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
#ifndef NYX_CORE_INCLUDED_POINT2I_H_
#define NYX_CORE_INCLUDED_POINT2I_H_

namespace Nyx 
{
	class Point2i {
	public:
		//--------------------------------------------------------------------------------------
		// メンバ変数
		//--------------------------------------------------------------------------------------
		/// メンバ変数
		union {
			struct {
				/// x値
				int  x;
				/// y値
				int  y;
			};
			/// 配列
			int elements[2];
		};

		//--------------------------------------------------------------------------------------
		// 定数
		//--------------------------------------------------------------------------------------
		/// ゼロ位置
		static const Point2i Zero;

		/// 単位位置
		static const Point2i Unit;

		//--------------------------------------------------------------------------------------
		// コンストラクタ・デストラクタ
		//--------------------------------------------------------------------------------------

		/**
		*
		*/
		Point2i():x(0), y(0){}

		/**
		*
		*/
		Point2i(int a, int b):x(a), y(b) {

		}

		/**
		*
		*/
		Point2i(int array[2]):x(array[0]), y(array[1]) {

		}

		/**
		*
		*/
		Point2i(const Point2i& p):x(p.x),y(p.y) {

		}

		/**
		*
		*/
		~Point2i() {}


		//--------------------------------------------------------------------------------------
		// 演算
		//--------------------------------------------------------------------------------------
		/**
		*
		* @param p 加算するPoint2i
		* @return 加算された
		*/
		Point2i operator +(const Point2i& p) const {
			return Point2i(x + p.x, y + p.y);
		}

		/**
		*
		*/
		Point2i operator -(const Point2i& p) const {
			return Point2i(x - p.x, y - p.y);
		} 

		/**
		*
		*/
		Point2i operator *(int value) const {
			return Point2i(x * value, y *value);
		}

		/**
		*
		*/
		Point2i operator /(int value) const {
			return Point2i(x / value, y / value);
		}
		//--------------------------------------------------------------------------------------
		// 代入演算
		//--------------------------------------------------------------------------------------
		/**
		*
		* @param
		* @return
		*/
		Point2i& operator +=(const Point2i & p) {
			x += p.x;
			y += p.y;

			return *this;
		}
		/**
		*
		* @param
		* @return
		*/
		Point2i& operator -=(const Point2i & p) {
			x -= p.x;
			y -= p.y;

			return *this;
		}
		
		/**
		*
		* @param
		* @return
		*/
		Point2i& operator *=(int value) {
			x *= value;
			y *= value;

			return *this;
		}
			/**
		*
		* @param
		* @return
		*/
		Point2i& operator /=(int value) {
			x /= value;
			y /= value;

			return *this;
		}
		//--------------------------------------------------------------------------------------
		// 論理演算
		//--------------------------------------------------------------------------------------
		/**
		*
		* @param
		* @return
		*/
		bool operator ==(const Point2i & p) const {
			return ((x == p.x) && (y == p.y));
		}

		/**
		*
		* @param
		* @return
		*/
		bool operator !=(const Point2i & p) const {
			return ((x != p.x) || (y != p.y));
		}
	};

}

#endif