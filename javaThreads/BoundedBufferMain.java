
package BoundedBuffer;


public class BoundedBufferMain {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        BoundedBuffer bf = new BoundedBuffer(10);
        Thread producerThread = new Thread(new Producer(bf));
        Thread consumerThread = new Thread(new Consumer(bf));
        producerThread.start();
        consumerThread.start();
    }

}
