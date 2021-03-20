import java.io.RandomAccessFile;
import java.util.Scanner;

public class BinarySearch {

    public static void main(String[] args) throws Exception {
        RandomAccessFile file = new RandomAccessFile("ordered_cep.dat","r");
        Scanner sc = new Scanner(System.in);

        System.out.println("Digite o CEP que deseja buscar: ");
        String cep = sc.nextLine();

        int positionFinded = searchCEP(file, cep);
        
        System.out.println((positionFinded != 0) ? 
            "O CEP " + cep + " foi encontrado na posição: " + positionFinded :
            "O CEP não foi encontrado!"
        );

        file.close();
        sc.close();
    }

    public static int searchCEP(RandomAccessFile file, String cep) throws Exception {
        Endereco address = new Endereco();

        long start = 0;
        long middle = 0; 
        long end = file.length() / 300L;     

        int comparation;
        boolean finded = false;

        int counter = 0;

        while (start < end && !finded) {
            middle = (end + start) / 2L;
            file.seek(middle * 300L);
            address.leEndereco(file);

            comparation = address.getCep().compareTo(cep);

            if(comparation == 0) {  
                finded = true;
            } else if(comparation < 0) {
                start = middle++; 
            } else {
                end = middle--; 
            }

            counter++;
        }

        return (finded) ? counter : 0;
    }
}