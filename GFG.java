// Java implementation of the approach
class GFG {

	// Function that returns true if the
	// passed character is a digit
	static boolean isDigit(char ch)
	{
		if (ch >= '0' && ch <= '9')
			return true;
		return false;
	}

	// Function to return the next index
	// of a non-digit character in the string
	// starting at the index i (returns -1 if
	// no such index is found)
	static int nextNonDigit(String str, int i)
	{

		// If the character at index i is a digit
		// then skip to the next character
		while (i < str.length()
			&& isDigit(str.charAt(i))) {
			i++;
		}

		// If no such index was found
		if (i >= str.length())
			return -1;
		return i;
	}

	// Function to append str the given number
	// of times to the StringBuilder
	
	static void appendRepeated(StringBuilder sb,
							String str, int times)
	{
		for (int i = 0; i < times; i++)
			sb.append(str);
	}

	// Function to return the string after
	// performing the given operations
	static String findString(String str, int n)
	{

		// To build the resultant string
		StringBuilder sb = new StringBuilder("");

		// Index of the first non-digit
		// character in the string
		int startStr = nextNonDigit(str, 0);

		// While there are substrings that
		// do not consist of digits
		while (startStr != -1) {

			// Find the ending of the substring
			int endStr = startStr;
			while ((endStr + 1) < n
				&& !isDigit(str.charAt(endStr + 1))) {
				endStr++;
			}

			// Starting index of the number
			int startNum = endStr + 1;

			// If no digit appears after
			// the current substring
			if (startNum == -1)
				break;

			// Find the index at which the
			// current number ends
			int endNum = startNum;
			while ((endNum + 1) < n
				&& isDigit(str.charAt(endNum + 1))) {
				endNum++;
			}

			// Parse the number from the substring
			int num = Integer.parseInt(str.substring(startNum,
													endNum + 1));

			// Repeat the current substring required number of times
			appendRepeated(sb, str.substring(startStr,
											endStr + 1), num);

			// Find the next non-digit character index
			startStr = nextNonDigit(str, endStr + 1);
		}

		// Return the resultant string
		return sb.toString();
	}

	// Driver code
	public static void main(String[] args)
	{
		String str = "g1ee1ks1for1g1e2ks1";
		int n = str.length();
		System.out.println(findString(str, n));
	}
}
