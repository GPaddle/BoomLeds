import java.awt.*; //<>//
import java.awt.event.*;
import java.awt.datatransfer.*;



PImage myImage;
boolean analyse=false, fin=false;

void setup() {
  selectInput("Select a file to process:", "fileSelected");
  size(600, 500);
}

void draw() {
  if (myImage!=null) {

    if (!analyse) {

      analyseImage();
    } else if (!fin) {
      background(0);

      int taille=min(height/myImage.height, width/myImage.width)-1;
      if (taille<1) {
        taille=1;
      }
      int x=myImage.width;
      int y=myImage.height;
      for (int i=y; i>=0; i--) {
        for (int j=x; j>=0; j--) {
          //println(taille);
          color c = myImage.get(j, i);
          stroke(c);
          fill(c);
          strokeWeight(taille);
          point(taille+taille*j, taille+taille*i);
        }
      }
      fin=true;
    }
  }
}






void analyseImage() {

  int x=myImage.width;
  int y=myImage.height;

  String selection = "";

  background(0);
  image(myImage, 0, 0);

  selection+="uint16_t tabName[";
  selection+=y;
  selection+="][";
  selection+=x;
  selection+="] =";
  selection+="{\n";
  for (int i=0; i<y; i++) {

    selection+="{";
    for (int j=0; j<x-1; j++) {
      color c = get(j, i);

      selection+=traitementCouleur(c);
      selection+=",\t";
    }
    color c = get(x-1, i);
    selection+=traitementCouleur(c);
    if (i==y-1) {
      selection+="}\n";
    } else {
      selection+="},\n";
    }
  }
  selection+="};";
  analyse=true;

  StringSelection data = new StringSelection(selection);
  Clipboard clipboard = Toolkit.getDefaultToolkit().getSystemClipboard();
  clipboard.setContents(data, data);

  print("Traitement OK\nPour analyser une nouvelle image, cliquer dans l'interface");
}







void fileSelected(File selection) {
  if (selection == null) {
    println("Window was closed or the user hit cancel.");

    exit();
  } else {
    //    println("User selected " + selection.getAbsolutePath());
    myImage = loadImage(selection.getAbsolutePath());
    image(myImage, 0, 0);
  }
}

void mouseClicked() {
  myImage=null;
  selectInput("Select a file to process:", "fileSelected");
  analyse=false;
  fin=false;
}

String traitementCouleur(color c) {
  if (red(c)+green(c)+blue(c)==0) {
    return "0";
  } else if (red(c)+green(c)+blue(c) == (3*255)) {
    return  "White";
  }else if (red(c)==255 && green(c)==0 && blue(c) == 0) {
    return  "Red";
  } else if (red(c)==0 && green(c)==255 && blue(c) ==0) {
    return  "Green";
  } else if (red(c)==0 && green(c)==0 && blue(c) == 255) {
    return "Blue";
  } else
    return "matrix.Color("+red(c)+","+green(c)+","+blue(c)+")";
}
