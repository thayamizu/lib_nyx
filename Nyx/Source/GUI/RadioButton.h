/********************************************************************************
*
*  The MIT License
*
* Copyright (c) 2010-2011 t.hayamizu
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
#ifndef NYX_CORE_INCLUDED_RADIO_Button_H_
#define NYX_CORE_INCLUDED_RADIO_Button_H_

#include "GUI/IRadioButton.h"

namespace Nyx {
	class IWindow;
	///ラジオボタン
	class RadioButton : public IRadioButton {
	public:
		//---------------------------------------------------------------------------------------
		//生成・破棄
		//---------------------------------------------------------------------------------------
		/**
		*
		*/
		RadioButton(HWND hwnd,tstring label, int x, int y, int width,int height, int id);
		/**
		*
		*/

		~RadioButton();
		/**
		*
		*/
		bool OnCreate(HWND hwnd, tstring label, int x, int y, int width,int height, int id);

		//--------------------------------------------------------------------------------------
		//ハンドルの取得
		//---------------------------------------------------------------------------------------
		/**
		* ウインドウハンドルの取得
		* @return HWND
		*/
		HWND GetHandle();
		//---------------------------------------------------------------------------------------
		//描画・更新
		//---------------------------------------------------------------------------------------
		/**
		* ウインドウを表示する
		*/
		void Show();
		/**
		* ウインドウを隠す
		*/
		void Hide();
		/**
		* ウインドウを更新する
		*/
		void Update();
		/**
		* ウインドウが表示されているか
		* @return trueならウインドウは表示されている
		*/
		bool IsShow();

		//---------------------------------------------------------------------------------------
		//コントロールの有効化と無効化
		//---------------------------------------------------------------------------------------
		/**
		* コントロールを有効化する
		*/
		void Activate();

		/**
		* コントロールを無効化する
		*/
		void Unactivate();

		/**
		* コントロールが有効かどうか
		* @return bool trueならコントロールは有効
		*/
		bool IsActivate() const;

		//---------------------------------------------------------------------------------------
		//値の取得・設定
		//---------------------------------------------------------------------------------------
		/**
		* コントロールのタイプを取得する
		* @return ControlType::enum_tの値
		*/
		ControlType::enum_t GetType() const;

		/**
		* ユーザーデータを取得する
		* @return void*
		*/
		void* GetUserData() const;

		/**
		* ユーザーデータを設定する
		* @param void* ユーザーデータ
		*/
		void SetUserData(void * data) ;

		/**
		* コントロールのIDを取得する
		* @return uint コントロールのID
		*/
		uint GetID() const;

		/**
		* コントロールのIDを設定する
		* @return コントロールのID
		*/
		void SetID(uint id)  ;

		/**
		* ウインドウのクライアント領域のサイズを取得する
		* @param Rect2i* ウインドウのクライアント領域のサイズ
		*/
		void GetSize(Rect2i* rect) const;

		/**
		* ウインドウのクライアント領域のサイズを設定する
		* @param Rect2i& ウインドウのクライアント領域のサイズ
		*/
		void SetSize(const Rect2i& rect);

		/**
		* ウインドウの位置を取得する
		* @param Point2i* p
		*/
		void GetPosition(Point2i* p) const;

		/**
		* ウインドウの位置を設定する
		*/
		void SetPosition(const Point2i& p);

		//----------------------------------------------------------------
		// ラジオボタン固有の操作
		//----------------------------------------------------------------
		/**
		* ラベルの取得
		* @return tstring& ラベル
		*/
		tstring GetLabel() const ;

		/**
		* ラベルの設定
		* @param const tstring& ラベル
		*/
		void SetLabel(const tstring& label) ;

		/**
		* ボタンがチェック状態かどうか
		* @return bool trueならチェックされている
		*/
		bool IsChecked() const ;

	private:
		///ボタンの表示ラベル
		tstring label;
		/// ハンドルインスタンス
		HWND hwnd;
		///ボタンID
		int id;
		///アトム
		ATOM atom;
		///表示されているかどうか
		bool isShow;
		///ユーザーデータ
		void * userData;
	};
}
#endif