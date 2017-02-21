public class matrixprodj {
    
    public static void OnMult (int m_ar, int m_br) {

        long t_start, t_end; // Start and end times for the matrix multiplication algorithm
        double ttime; // Total time it took the matrix multiplication algorithm to run

        double temp;
        int i, j, k;

        double pha[] = new double[m_ar*m_ar];
        double phb[] = new double[m_ar*m_ar];
        double phc[] = new double[m_ar*m_ar];

        // Initializing array pha
        for(i = 0; i < m_ar; i++) {
            for(j = 0; j < m_ar; j++) {
                pha[i*m_ar + j] = (double)1.0;
            }
        }

        // Initializing array phb
        for(i = 0; i < m_br; i++) {
            for(j = 0; j < m_br; j++) {
                phb[i*m_br + j] = (double)(i+1);
            }
        }

        // Start registering the matrix multiplication algorithm time
        t_start = System.nanoTime();

        for(i = 0; i < m_ar; i++) {
            for(j = 0; j < m_br; j++) {
                temp = 0;
                for(k = 0; k < m_ar; k++) {
                    temp += pha[i*m_ar + k] * phb[k*m_br + j];
                }
                phc[i*m_ar + j] = temp;
            }
        }

        // Finish registering the matrix multiplication algorithm time
        t_end = System.nanoTime();
        ttime = (t_end - t_start) / 1000000000.0; // Convert from nanoseconds to seconds

        System.out.println("Time: " + ttime + " seconds");

        // Print out results

        System.out.println("Result matrix: ");
        for(i = 0; i < 1; i++) {
            for(j = 0; j < Math.min(10, m_br); j++) {
                System.out.print(phc[j] + " ");
            }
        }
        System.out.println("");
    }

    public static void main(String[] args) {
        int oper, m_size;

        if (args.length != 2) {
            System.out.println("Error! Expected two args: Operation(0 = Multiplication / 1 = Multiplication by line) MatrixSize");
        }

        oper = Integer.parseInt(args[0]);
        m_size = Integer.parseInt(args[1]);

        if(oper == 0)
            OnMult(m_size, m_size);
    }
}