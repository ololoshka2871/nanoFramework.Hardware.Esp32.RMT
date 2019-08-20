using System;

namespace nanoFramework.Hardware.Esp32.RMT.Tx
{
	public class PulseCommand
	{
		#region Fields

		public bool level1 = false;
		public bool level2 = false;

		public const int SerialisedSize = 4;
		private const UInt16 MAX_DURATION = 32768;

		private UInt16 mDuration1 = 0;
		private UInt16 mDuration2 = 0;

		#endregion Fields

		#region Constructors

		public PulseCommand(UInt16 duration1, bool level1, UInt16 duration2, bool level2)
		{
			Duration1 = duration1;
			Duration2 = duration2;
			this.level1 = level1;
			this.level2 = level2;
		}

		public PulseCommand()
		{
		}

		#endregion Constructors

		#region Properties

		public UInt16 Duration1
		{
			get => mDuration1;
			set
			{
				CheckDuration(value);
				mDuration1 = value;
			}
		}

		public UInt16 Duration2
		{
			get => mDuration2;
			set
			{
				CheckDuration(value);
				mDuration2 = value;
			}
		}

		#endregion Properties

		#region Methods

		protected static void CheckDuration(UInt16 v)
		{
			if (v > MAX_DURATION)
			{
				throw new ArgumentOutOfRangeException("Duration maxt be <= 32768");
			}
		}

		public static PulseCommand EndMarker() => new PulseCommand(0, true, 0, false);

		public bool isPulsed() => level1 != level2;

		protected UInt16 AppendDuration2(UInt16 duration)
		{
			int newDuration = Duration2 + duration;
			if (newDuration > MAX_DURATION)
			{
				Duration2 = MAX_DURATION;
				return (UInt16)(newDuration - MAX_DURATION);
			}
			else
			{
				Duration2 = (UInt16)newDuration;
				return 0;
			}
		}

		public UInt16 AppendDuration(UInt16 duration)
		{
			if (isPulsed())
			{
				return AppendDuration2((UInt16)duration);
			}

			int newDuration = Duration1 + Duration2 + duration;
			if (newDuration > MAX_DURATION)
			{
				Duration1 = MAX_DURATION;
				Duration2 = 0;
				newDuration -= MAX_DURATION;
				return AppendDuration2((UInt16)newDuration);
			}
			else
			{
				Duration1 = (UInt16)newDuration;
				Duration2 = 0;
				return 0;
			}
		}

		public bool EndsWithLevel(bool state) 
			=> Duration2 > 0 ? level2 == state : level1 == state;

		public void SerialiseTo(byte[] buf, int offset)
		{
			// <duration1><level1><duration2><level2>
			// 0---------15------16---------30------31

			UInt32 v = mDuration1 |
				(level1 ? 1u : 0) << 15 |
				(uint)mDuration2 << 16 |
				(level2 ? 1u : 0) << 31;
			byte[] intBytes = BitConverter.GetBytes(v);
			//if (BitConverter.IsLittleEndian)
			//	Array.Reverse(intBytes);

			Array.Copy(intBytes, 0, buf, offset, intBytes.Length);
		}

		#endregion Methods
	}
}