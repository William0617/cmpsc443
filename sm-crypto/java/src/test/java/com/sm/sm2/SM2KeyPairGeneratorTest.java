/*
 * Copyright (c) 2016 BeiJing JZYT Technology Co. Ltd
 * www.idsmanager.com
 * All rights reserved.
 *
 * This software is the confidential and proprietary information of
 * BeiJing JZYT Technology Co. Ltd ("Confidential Information").
 * You shall not disclose such Confidential Information and shall use
 * it only in accordance with the terms of the license agreement you
 * entered into with BeiJing JZYT Technology Co. Ltd.
 */
package com.sm.sm2;

import org.testng.annotations.Test;


import static org.testng.Assert.assertNotNull;

/**
 * @author William Sun
 */
public class SM2KeyPairGeneratorTest {

    @Test
    public void generateKeyPairTest() {

        //case1：HEX
        SM2KeyPair keyPair1 = SM2KeyPairGenerator.generateKeyPair(true);
        final String publicKey1 = keyPair1.getHexPublicKey();
        assertNotNull(publicKey1);
        final String privateKey1 = keyPair1.getHexPrivateKey();
        assertNotNull(privateKey1);

        //case2：Base64
        SM2KeyPair keyPair2 = SM2KeyPairGenerator.generateKeyPair(true);
        final String publicKey2 = keyPair2.getBase64PublicKey();
        assertNotNull(publicKey2);
        final String privateKey2 = keyPair2.getBase64PrivateKey();
        assertNotNull(privateKey2);

    }
}
