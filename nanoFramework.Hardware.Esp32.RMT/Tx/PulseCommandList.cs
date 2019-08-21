using System.Collections;

namespace nanoFramework.Hardware.Esp32.RMT.Tx
{
	public class PulseCommandList : IPulseCommandList
	{
		#region Fields

		protected ArrayList commands = new ArrayList();

		#endregion Fields

		#region Methods

		public virtual IPulseCommandList AddCommand(PulseCommand cmd)
		{
			commands.Add(cmd);
			return this;
		}

		public virtual IPulseCommandList AddState(bool level, ushort duration)
		{
			var last_command = LastCommand();
			if (last_command == null)
			{
				AddCommand(level, duration);
			}
			else
			{
				var res = last_command.AddLevel(level, ref duration);
				if (res != PulseCommand.ApplyResult.DONE)
				{
					AddCommand(level, duration);
				}
			}
			return this;
		}

		public virtual byte[] Serialise()
		{
			AddCommand(PulseCommand.EndMarker());
			var result = new byte[commands.Count * PulseCommand.SerialisedSize];
			for (int i = 0, offset = 0; i < commands.Count; ++i, offset += PulseCommand.SerialisedSize)
			{
				((PulseCommand)commands[i]).SerialiseTo(result, offset);
			}
			return result;
		}

		protected void AddCommand(bool state, ushort Duration) =>
			AddCommand(new PulseCommand(Duration, state, 0, state));

		protected PulseCommand LastCommand()
		{
			if (commands.Count == 0)
			{
				return null;
			}

			return (PulseCommand)commands[commands.Count - 1];
		}

		#endregion Methods
	}
}