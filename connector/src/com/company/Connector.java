package com.company;

import org.apache.http.HttpResponse;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.entity.StringEntity;
import org.apache.http.impl.client.CloseableHttpClient;
import org.apache.http.impl.client.HttpClients;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Connector {
    private static String url = "http://localhost:3000/saveTag";

    private String RFIDtag;

    public Connector(String RFIDtag){
        this.RFIDtag = RFIDtag;
    }

    public void sendPOST() throws IOException {
        CloseableHttpClient httpclient = HttpClients.createDefault();

        HttpPost httpPost = new HttpPost(url);

        httpPost.setHeader("Accept", "application/json");
        httpPost.setHeader("Content-type", "application/json");


        String inputJson = "{\"IDtag\": \"111111111"+ RFIDtag +"\" }";

        StringEntity stringEntity = new StringEntity(inputJson);
        httpPost.setEntity(stringEntity);

        System.out.println("Executing request " + httpPost.getRequestLine());

        HttpResponse response = httpclient.execute(httpPost);

        BufferedReader br = new BufferedReader(
                new InputStreamReader((response.getEntity().getContent())));

        if (response.getStatusLine().getStatusCode() != 200) {
            throw new RuntimeException("Failed : HTTP error code : "
                    + response.getStatusLine().getStatusCode());
        }

        StringBuffer result = new StringBuffer();
        String line = "";
        while ((line = br.readLine()) != null) {
            System.out.println("Response : \n"+result.append(line));
        }
    }
}


