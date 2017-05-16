package blockchain;

import java.security.MessageDigest;

public class BlockData
{
	private final String data, hash, preHash;
	private int nonce;
	
	public BlockData(final String data, final String preHash)
	{
		this.data = data;
		this.preHash = preHash;
		this.hash = computeHash();
	}
	
	private String computeHash()
	{
		String tempHash;
		this.nonce = 0;
		
		while( !isSigned( tempHash = sha256(nonce++ + this.data + this.preHash) ) );
		
		return tempHash;
	}
	
	private String sha256(String base)
	{
	    try
	    {
	        MessageDigest digest = MessageDigest.getInstance("SHA-256");
	        byte[] hash = digest.digest(base.getBytes("UTF-8"));
	        StringBuffer hexString = new StringBuffer();

	        for (int i = 0; i < hash.length; i++)
	        {
	            String hex = Integer.toHexString(0xff & hash[i]);
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
		return this.data;
	}
}