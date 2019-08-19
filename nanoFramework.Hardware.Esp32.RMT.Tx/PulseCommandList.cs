using System;

namespace nanoFramework.Hardware.Esp32.RMT.Tx
{
	public class PulseCommandList : IPulseCommandList
	{
		#region Methods

		public virtual IPulseCommandList AddPulse(ushort duration0, ushort duration1)
		{
			throw new NotImplementedException();
		}

		public virtual IPulseCommandList AddState(bool state, ushort Duration)
		{
			throw new NotImplementedException();
		}

		public virtual byte[] Serialise()
		{
			throw new NotImplementedException();
		}

		#endregion Methods
	}
}