namespace MapEditor
{
	internal static class Program
	{
		internal static List<EditorScheme> EditorSchemes = new();

		[STAThread]
		internal static void Main()
		{
			LoadAllSchemes();

			ApplicationConfiguration.Initialize();
			Application.Run(new EditorForm());
		}
		internal static void LoadAllSchemes()
		{
			var files = Directory.GetFiles("./Schemes", "*.json");

			for (int i = 0; i < files.Length; i++)
			{
				var file = files[i];

				try
				{
					EditorSchemes.Add(EditorScheme.LoadScheme(File.ReadAllText(file)));
				}
				catch
				{
					MessageBox.Show($"Couldn't load editor scheme \"{file}\", skipping...", "Warning", MessageBoxButtons.OK, MessageBoxIcon.Warning);
				}
			}
		}
	}
}