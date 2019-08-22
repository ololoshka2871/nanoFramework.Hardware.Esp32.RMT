using System;

namespace nanoFramework.Hardware.Esp32.RMT.Tx
{
	public class PulseCommand
	{
		public enum ApplyResult { DONE, OVERFLOW, REJECTED };

		#region Fields

		public bool level1 = false;
		public bool level2 = false;

		public const int SerialisedSize = 4;
		public const UInt16 MAX_DURATION = 32767;

		private UInt16 mDuration1 = 1;
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

		private ApplyResult AddLevel1(bool level, ref UInt16 duration)
		{
			if (level1 != level)
				return ApplyResult.REJECTED;

			mDuration1 += duration;
			duration = 0;
			if (mDuration1 > MAX_DURATION)
			{
				duration = (UInt16)(mDuration1 - MAX_DURATION);
				return ApplyResult.OVERFLOW;
			}
			return ApplyResult.DONE;
		}

		private ApplyResult AddLevel2(bool level, ref UInt16 duration)
		{
			if (level2 != level)
				return ApplyResult.REJECTED;

			mDuration2 += duration;
			duration = 0;
			if (mDuration2 > MAX_DURATION)
			{
				duration = (UInt16)(mDuration2 - MAX_DURATION);
				return ApplyResult.OVERFLOW;
			}
			return ApplyResult.DONE;
		}

		public ApplyResult AddLevel(bool level, ref UInt16 duration)
		{
			if (isPulsed())
			{
				return AddLevel2(level, ref duration);
			}
			else
			{
				if (Duration2 == 0) {
					var r = AddLevel1(level, ref duration);
					level2 = level;
					return (r != ApplyResult.DONE) ? AddLevel2(level, ref duration) : r;
				}
				return AddLevel2(level, ref duration);
			}
		}

		public bool isPulsed() => level1 != level2;
		
		public void SerialiseTo(byte[] buf, int offset)
		{
			// <duration1><level1><duration2><level2>
			// 0---------15------16---------30------31

			UInt32 v = mDuration1 |
				(level1 ? 1u : 0) << 15 |
				(uint)mDuration2 << 16 |
				(level2 ? 1u : 0) << 31;
			byte[] intBytes = BitConverter.GetBytes(v);
			Array.Copy(intBytes, 0, buf, offset, intBytes.Length);
		}

		#endregion Methods
	}
}