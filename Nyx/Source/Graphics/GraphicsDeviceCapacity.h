#ifndef NYX_CORE_INCLUDED_GRAPHICS_DEVICE_CAPACITY_H_
#define NYX_CORE_INCLUDED_GRAPHICS_DEVICE_CAPACITY_H_

namespace Nyx {

	class GraphicsDeviceCapacity
	{
	public:
		GraphicsDeviceCapacity();
		void LookupGraphicsDeviceCapacity();
	private:
		struct PImpl;
		std::shared_ptr<PImpl> pimpl_;
	};

	

}
#endif