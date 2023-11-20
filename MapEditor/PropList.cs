using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MapEditor
{
	internal class PropList
	{
		internal string RawText;
		internal Dictionary<string, string> PropMap;

		internal PropList(string text)
		{
			RawText = text;
			PropMap = new();
			UpdatePropMap();
		}

		internal void UpdateRawText()
		{
			RawText = string.Empty;

			for (int i = 0; i < PropMap.Count; i++)
			{
				var pair = PropMap.ElementAt(i);
				RawText += pair.Key + '=' + pair.Value + '\n';
			}

			RawText = RawText[..^2];
		}
		internal void UpdatePropMap()
		{
			PropMap.Clear();
			var lines = RawText.Split('\n');

			for (int i = 0; i < lines.Length; i++)
			{
				var line = lines[i];
				var parts = line.Split("=");
				var key = parts[0];
				var value = parts[1];

				PropMap[key] = value;
			}
		}
	}
}
