import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.Scanner;

public class RBT {

    public static void main(String[] args) throws IOException {
        RBTree t = new RBTree();
        File file = new File("C:\\Users\\alyfe\\Downloads\\englishDictionary.txt");
        FileReader fr=new FileReader(file);
        Scanner scanner = new Scanner(fr);
        while (scanner.hasNextLine()){ //fill the tree up
            String st=scanner.nextLine();
            Node x=new Node(null,st);
            t.insert(x);
        }
        scanner.close();
        System.out.println("Tree size: "+t.getSize());
        System.out.println("Tree Depth: "+t.getHeight());
        String key;
        int choice=0;
        Scanner c = new Scanner(System.in);
        Scanner ch = new Scanner(System.in);
        System.out.println(t.getRoot().getWord());
        do{
            System.out.println("Choose one of the following options:");
            System.out.println("1-insert in Red Black Tree");
            System.out.println("2-print the tree(inorder Traversal)");
            System.out.println("3-Lookup a word in the tree");
            System.out.println("4-print size of tree");
            System.out.println("5-print Depth of tree");
            System.out.println("6-exit");
            choice=ch.nextInt();
            switch(choice){
                case 1:

                    System.out.println("enter the word you want to insert:\n");
                    key=c.nextLine();
                    Node ins=new Node(null,key);
                    t.insert(ins);
                    break;
                case 2:
                    t.inOrderTraversal(t.getRoot());
                    break;
                case 3:
                    System.out.println("enter the word you want to find\n");
                    key=c.nextLine();
                    t.lookup(t.getRoot(),key);
                    break;
                case 4:
                    System.out.println("Size of tree=  "+t.getSize()+"\n");
                    break;
                 case 5:
                     System.out.println("Depth of tree=  "+t.getHeight()+"\n");
                     break;
                case 6:
                    System.out.println("exiting thank u ");
                    break;
            }

        }while(choice!=6);
    }
}