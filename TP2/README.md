# CPAR
Repository for the Parallel Computing class at FEUP.

## TP2

### Project setup 

#### Connecting through SSH to a remote computer

* Create the folder in the directory ~/.ssh if one isn't present yet (```mkdir ~/.ssh```) on the computer you will access through ssh.

* Open the folder (```cd ~/.ssh```) and run the command: ```ssh-keygen -t rsa```. When prompted for the file name, keep the default name (id_rsa). When prompted for a password, leave blank it and its confirmation field. This will generate a private and public key that you can use to grant access to the computer to anyone with the private key.

* Afterwards, run the command: ```cat id_rsa.pub >> authorized_keys```. This will copy the public key from your key combo to the authorized keys file.

* Copy the id_rsa.pub file to a USB pen drive and plug it into the computer you will be running your OpenMPI program from.

* Once plugged in, you can open a terminal at the location of your USB pen drive. In this terminal, run the command: ```ssh YYY@192.168.XXX.XXX -i id_rsa.pub``` where YYY is your username at the remote.

* Once prompted for a password, type in your password associated at the username on the remote PC.

* Assuming everything went smoothly, you should now have access to the remote PC through SSH! Keep in mind you can repeat these steps for multiple different computers. If you're faced with any errors running these commands, or want to try accessing multiple computers remotely without being asked for a password, you can [check out this link](https://www.open-mpi.org/faq/?category=rsh#ssh-keys).

* Next up is the compilation of your OpenMPI program: ```mpiCC.openmpi -o prog prog.cpp```.

* Afterwards, create a new file called hostfile (with no extension) that contains a list of the PCs where you want to run your program (e.g. hostfile will have lines of the type: 192.168.XXX.XXX cpu=4, where CPU is the number of cores you want operating on the program).

* Finally, run the program with OpenMPI through the command: ```mpirun --hostfile hostfile -np 4 prog```, where np is the number of copies you want to run of the program on the given cores.

* And that's it. You're ready to carry CPAR's second project!

### Project hand-in

* Article

* Experiment Results