using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Json;
using System.Text.Json.Serialization;
using System.Threading.Tasks;

namespace MapEditor
{
	internal class EditorScheme
	{
		internal string? Class;
		internal string? Species;
		internal string? ClassDescription;
		internal string? SpeciesDescription;
		internal List<string>? RequiredProperties;
		internal List<string>? AllProperties;
		internal Dictionary<string, string>? PropertyDescriptions;
		internal Dictionary<string, PropertyType>? PropertyTypes;

		internal static EditorScheme LoadScheme(string data) => JsonSerializer.Deserialize<EditorScheme>(data)!;
	}
	internal enum PropertyType
	{
		Any, String, Number, Boolean
	}
}
