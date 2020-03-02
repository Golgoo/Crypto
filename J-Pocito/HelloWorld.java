import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.math.BigInteger;
import java.security.InvalidAlgorithmParameterException;
import java.security.InvalidKeyException;
import java.security.KeyFactory;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.security.interfaces.RSAPublicKey;
import java.security.spec.InvalidKeySpecException;
import java.security.spec.RSAPublicKeySpec;

import javax.crypto.BadPaddingException;
import javax.crypto.Cipher;
import javax.crypto.CipherInputStream;
import javax.crypto.IllegalBlockSizeException;
import javax.crypto.KeyGenerator;
import javax.crypto.NoSuchPaddingException;
import javax.crypto.SecretKey;
import javax.crypto.spec.IvParameterSpec;

public class HelloWorld {

	public static void main(String[] args) throws IOException {
		SecureRandom random = new SecureRandom();

        //Creation d'une clef secrete AES courte aléatoire
        KeyGenerator keyGen = null;
		try {
			keyGen = KeyGenerator.getInstance("AES");
		} catch (NoSuchAlgorithmException e1) {
			e1.printStackTrace();
		}
		keyGen.init(128);
        SecretKey secretKey = keyGen.generateKey();
        
        //Creation d'un vecteur d'initialisation aléatoire:
        byte[] iv = new byte[16];
        random.nextBytes(iv);
        IvParameterSpec ivspec = new IvParameterSpec(iv);

        
        FileInputStream fis = null;
	    FileOutputStream fos = null;
	    CipherInputStream cis = null;
	    
	    Cipher cipher = null;
	    
	    BigInteger modulus = new BigInteger("94f28651e58a75781cfe69900174b86f855f092f09e3da2ad86b4ed964a84917e5ec60f4ee6e3adaa13962884e5cf8dae2e0d29c6168042ec9024ea11176a4ef031ac0f414918b7d13513ca1110ed80bd2532f8a7aab0314bf54fcaf621eda74263faf2a5921ffc515097a3c556bf86f2048a3c159fccfee6d916d38f7f23f21", 16);
        BigInteger pubExp = new BigInteger("44bb1ff6c2b674798e09075609b7883497ae2e2d7b06861ef9850e26d1456280523319021062c8743544877923fe65f85111792a98e4b887de8ffd13aef18ff7f6f736c821cfdad98af051e7caaa575d30b54ed9a6ee901bb0ffc17e25d444f8bfc5922325ee2ef94bd4ee15bede2ea12eb623ad507d6b246a1f0c3cc419f155", 16);
        RSAPublicKeySpec pubKeySpec = new RSAPublicKeySpec(modulus, pubExp);
        
		try {
			
			fis = new FileInputStream(args[0]);
			fos = new FileOutputStream(args[1]);
			
			// Chiffrement RSA de la clef courte AES
			KeyFactory keyFactory = KeyFactory.getInstance("RSA");
	        RSAPublicKey key = (RSAPublicKey) keyFactory.generatePublic(pubKeySpec);
	        Cipher key_cipher = Cipher.getInstance("RSA/ECB/PKCS1Padding");
	        key_cipher.init(Cipher.ENCRYPT_MODE, key);
	        byte[] secretKeyEncrypt = key_cipher.doFinal(secretKey.getEncoded());
	        //Ecriture du chiffré RSA de la clef courte AES
	        fos.write(secretKeyEncrypt);
	        
	        //Ecriture du vecteur d'initialisation :
	        fos.write(iv);
	        
	        //Initialisation AES/CBC/PKCS5
	        cipher = Cipher.getInstance("AES/CBC/PKCS5Padding");
			cipher.init(Cipher.ENCRYPT_MODE, secretKey, ivspec);
			cis = new CipherInputStream(fis, cipher);

			//Chiffrement bloc par bloc et écriture simultanée
			byte[] b = new byte[16];
			int i = cis.read(b);
			while( i != -1) {
				fos.write(b, 0, i);
				i = cis.read(b);
			}

		} catch (NoSuchAlgorithmException | InvalidKeySpecException | InvalidKeyException | NoSuchPaddingException | IllegalBlockSizeException | BadPaddingException | InvalidAlgorithmParameterException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} finally {
			if(fos != null)
				fos.close();
			if(fis != null)
				fis.close();
		}
	}
}
