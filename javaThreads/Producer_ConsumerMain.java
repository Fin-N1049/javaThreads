
package Producer_Consumer;


public class Producer_ConsumerMain {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        Producer_Consumer pc=new Producer_Consumer();
        new Producer(pc);
        new Consumer(pc);
    }
    
}
