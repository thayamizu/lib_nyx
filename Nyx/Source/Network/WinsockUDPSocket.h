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
#ifndef NYX_CORE_INCLUDED_WINSOCK_UDP_SERVER_SOCKET_H_
#define NYX_CORE_INCLUDED_WINSOCK_UDP_SERVER_SOCKET_H_

namespace Nyx {
	///UDPソケット
	class WinsockUDPSocket {
	public:
		/**
		*　コンストラクタ
		*/
		WinsockUDPSocket(const char* address, ushort port);
		
		
		/**
		*　デストラクタ
		*/
		~WinsockUDPSocket();


		/**
		* サーバーにデータを送信します
		* @param char*   送信バッファ
		* @param size_t  送信バッファの長さ
		* @return size_t 送信バイト数
		*/
		size_t Send(const WinsockUDPSocket& destination, char *buffer, size_t bufferSize);


		/**
		* サーバーからデータを受信します
		* @param char*  受信バッファ
		* @param size_t 受信バッファの長さ
		* @return size_ 受信バイト数
		*/
		size_t Recieve(const WinsockUDPSocket& source, char *buffer, size_t bufferSize);
	private:
		SOCKET      socket_;  ///< 接続先のソケット
		sockaddr_in address_; ///< 接続元のアドレス情報
	};
}
#endif
