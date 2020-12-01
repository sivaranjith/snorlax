package blockchain;

import java.security.MessageDigest;

final class BlockData<T>
{
	private final T data;
	private final String hash, preHash;
	private long nonce;
	
	public BlockData(final T data, final String preHash)
	{
		this.data = data;
		this.preHash = preHash;
		this.hash = computeHash();
	}
	
	private String computeHash()
	{
		String tempHash;
		this.nonce = 0;
		
		while( !isSigned( tempHash = sha256(nonce++ + this.data.toString() + this.preHash) ) );
		
		return tempHash;
	}
	
	private String sha256(String base)
	{
	    try
	    {
	    	final MessageDigest digest = MessageDigest.getInstance("SHA-256");
	    	final byte[] hash = digest.digest(base.getBytes("UTF-8"));
	    	final StringBuffer hexString = new StringBuffer();
	    	
	        for (int i = 0; i < hash.length; i++)
	        {
	        	final String hex = Integer.toHexString(0xff & hash[i]);
	            if(hex.length() == 1) hexString.append('0');
	            hexString.append(hex);
	        }

	        return hexString.toString();
	    }
	    catch(Exception ex)
	    {
	       throw new RuntimeException(ex);
	    }
	}
	
	private boolean isSigned(final String hash)
	{
		return hash.startsWith("0000");
	}
	
	public String getHash()
	{
		return this.hash;
	}
	
	@Override
	public String toString()
	{
		return this.data.toString();
	}
}