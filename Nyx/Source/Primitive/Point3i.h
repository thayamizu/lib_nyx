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
#ifndef NYX_CORE_INCLUDED_POINT3I_H_
#define NYX_CORE_INCLUDED_POINT3I_H_

namespace Nyx 
{
	class Point3i {
	public:
		//--------------------------------------------------------------------------------------
		// メンバ変数
		//--------------------------------------------------------------------------------------
		/// メンバ変数
		union {
			struct {
				/// x値
				int x;
				/// y値
				int y;
				/// z値
				int z;
			};
			/// 配列
			int elements[3];
		};

		//--------------------------------------------------------------------------------------
		// 定数
		//--------------------------------------------------------------------------------------
		/// ゼロ位置
		static const Point3i Zero;

		/// 単位位置
		static const Point3i Unit;

		//--------------------------------------------------------------------------------------
		// コンストラクタ・デストラクタ
		//--------------------------------------------------------------------------------------
		/**
		*
		*/
		Point3i():x(0), y(0), z(0){}
		/**
		*
		*/
		Point3i(int a, int b, int c):x(a), y(b), z(c) {

		}
		/**
		*
		*/
		Point3i(int array[3]):x(array[0]), y(array[1]),z(array[2]) {

		}
		/**
		*
		*/
		Point3i(const Point3i& p):x(p.x),y(p.y),z(p.z) {

		}

		/**
		*
		*/
		~Point3i() {}


		//--------------------------------------------------------------------------------------
		// 演算
		//--------------------------------------------------------------------------------------
		/**
		*
		* @param p 加算するPoint3i
		* @return 加算された
		*/
		Point3i operator +(const Point3i& p) const {
			return Point3i(x + p.x, y + p.y, z + p.z);
		}
		/**
		*
		*/
		Point3i operator -(const Point3i& p) const {
			return Point3i(x - p.x, y - p.y, z - p.z);
		} 
		/**
		*
		*/
		Point3i operator *(float value) const {
			return Point3i(x * (int)value, y * (int)value, z * (int)value);
		}
		/**
		*
		*/
		Point3i operator /(float value) const {
			return Point3i(x / (int)value, y / (int)value, z / (int)value);
		}//--------------------------------------------------------------------------------------
		// 代入演算
		//--------------------------------------------------------------------------------------
		/**
		*
		* @param
		* @return
		*/
		Point3i& operator +=(const Point3i & p) {
			x += p.x;
			y += p.y;
			z += p.z;

			return *this;
		}
		/**
		*
		* @param
		* @return
		*/
		Point3i& operator -=(const Point3i & p) {
			x -= p.x;
			y -= p.y;
			z -= p.z;

			return *this;
		}
		/**
		*
		* @param
		* @return
		*/
		Point3i& operator *=(float value) {
			x *= (int)value;
			y *= (int)value;
			z *= (int)value;

			return *this;
		}

		/**
		*
		* @param
		* @return
		*/
		Point3i& operator /=(float value) {
			x /= (int)value;
			y /= (int)value;
			z /= (int)value;

			return *this;
		}//--------------------------------------------------------------------------------------
		// 論理演算
		//--------------------------------------------------------------------------------------
		/**
		*
		* @param
		* @return
		*/
		bool operator ==(const Point3i & p) const {
			return ((x == p.x) && (y == p.y) && (z == p.z));
		}

		/**
		*
		* @param
		* @return
		*/
		bool operator !=(const Point3i & p) const {
			return !(*this == p);
		}
	};
}

#endif