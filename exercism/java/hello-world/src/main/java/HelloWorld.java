final public class HelloWorld
{
    public static String hello(final String name)
    {
        return "Hello, " + getSpectatorName(name) + "!";
    }

    private static String getSpectatorName(final String name)
    {
	return isValidName(name) ? name : "World";
    }

    private static boolean isValidName(final String name)
    {
	return !(name == null || "".equals(name));
    }
}
