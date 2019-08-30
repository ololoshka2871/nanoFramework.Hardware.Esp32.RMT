using System;
using System.Runtime.CompilerServices;

namespace nanoFramework.Hardware.Esp32.RMT.Tx
{
	/// <summary>
	/// ESP32 RMT module command
	/// 
	/// see [esp32-idf]/components/soc/esp32/include/soc/rmt_struct.h : 234 for more info
	/// </summary>
	public class PulseCommand
	{
		/// <summary>
		/// Result of state merging
		/// </summary>
		public enum ApplyResult {
			DONE, /// New State is fully merged into command
			OVERFLOW, /// New state is partially merged, but state counter overflow occurred
			REJECTED /// Can't merge new state into this command
		};

		#region Fields

		/// <summary>
		/// Command level 1
		/// </summary>
		public bool level1 = false;

		/// <summary>
		/// Command level 2
		/// </summary>
		public bool level2 = false;

		private UInt16 mDuration1 = 1;
		private UInt16 mDuration2 = 0;

		/// <summary>
		/// Equals with sizeof(rmt_item32_t)
		/// </summary>
		public const int SerialisedSize = 4;

		/// <summary>
		/// Max value of rmt_item32_t::durationX (15 bit unsigned value)
		/// </summary>
		public const UInt16 MAX_DURATION = 32767;

		#endregion Fields

		#region Constructors

		/// <summary>
		/// Create new pulse command
		/// 
		/// Referenced to rmt_item32_t
		/// </summary>
		/// <param name="duration1">Level 1 duration in chanel ticks</param>
		/// <param name="level1">logic outlut level 1</param>
		/// <param name="duration2">Level 2 duration in chanel ticks</param>
		/// <param name="level2">logic outlut level 1</param>
		public PulseCommand(UInt16 duration1, bool level1, UInt16 duration2, bool level2)
		{
			Duration1 = duration1;
			Duration2 = duration2;
			this.level1 = level1;
			this.level2 = level2;
		}

		/// <summary>
		/// Create empty pulse command
		/// Outputs logick level 0 for 1 RMT channel tick
		/// </summary>
		public PulseCommand()
		{
		}

		#endregion Constructors

		#region Properties

		/// <summary>
		/// Level1 duration in RMT chanel ticks
		/// </summary>
		public UInt16 Duration1
		{
			get => mDuration1;
			set
			{
				CheckDuration(value);
				mDuration1 = value;
			}
		}

		/// <summary>
		/// Level2 duration in RMT chanel ticks
		/// </summary>
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

		/// <summary>
		/// Copy date from reference command
		/// </summary>
		/// <param name="reference">Reference command</param>
		public void Assign(PulseCommand reference)
		{
			level1 = reference.level1;
			level2 = reference.level2;
			mDuration1 = reference.mDuration1;
			mDuration2 = reference.mDuration2;
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

		/// <summary>
		/// Try Add logick state to this command
		/// </summary>
		/// <param name="level">Output logick level</param>
		/// <param name="duration">Output duration in RMT chanel ticks</param>
		/// <returns>see enum ApplyResult</returns>
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

		/// <summary>
		/// Get command pulses of flat level
		/// </summary>
		/// <returns>true, if level1 equals to leve2</returns>
		public bool isPulsed() => level1 != level2;

		/// <summary>
		/// Convert instance to byte array representation of rmt_item32_t and write to designed place
		/// </summary>
		/// <param name="buf">Destination array to write result</param>
		/// <param name="offset">offset in destination array</param>
		public void SerialiseTo(byte[] buf, int offset)
		{
			// <duration1><level1><duration2><level2>
			// 0---------15------16---------30------31
			SerialiseTo(buf, offset, mDuration1, mDuration2, level1, level2);
		}

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void SerialiseTo(byte[] buf, int offset, UInt16 Duration1, UInt16 Duration2, bool level1, bool level2);

		#endregion Methods
	}
}