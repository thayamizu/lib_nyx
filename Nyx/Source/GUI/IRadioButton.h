#ifndef NYX_CORE_INCLUDED_IRADIO_BUTTON_H_
#define NYX_CORE_INCLUDED_IRADIO_BUTTON_H_
#include "GUI/IControl.h"
#include "Utility/Type.h"
namespace Nyx 
{
	///ラジオボタンインタフェース
	class IRadioButton : public IControl
	{
	public:
		//----------------------------------------------------------------
		//構築・破壊
		//----------------------------------------------------------------
		virtual ~IRadioButton() {}

		//----------------------------------------------------------------
		// ラジオボタン固有の操作
		//----------------------------------------------------------------
		/**
		* ラベルの取得
		* @return tstring& ラベル
		*/
		virtual tstring GetLabel() const = 0;

		/**
		* ラベルの設定
		* @param const tstring& ラベル
		*/
		virtual void SetLabel(const tstring& label) = 0;

		/**
		* ボタンがチェック状態かどうか
		* @return bool trueならチェックされている
		*/
		virtual bool IsChecked() const = 0;
	};
}
#endif