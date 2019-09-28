import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import java.awt.*; 
import java.awt.event.*; 
import java.awt.datatransfer.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class analyse_image extends PApplet {







PImage myImage;
boolean analyse=false, fin=false;

public void setup() {
  selectInput("Select a file to process:", "fileSelected");
  
}

public void draw() {
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
          int c = myImage.get(j, i);
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






public void analyseImage() {

  int x=myImage.width;
  int y=myImage.height;

  String selection = "";

  background(0);
  image(myImage, 0, 0);

  selection+="long tab[";
  selection+=y;
  selection+="][";
  selection+=x;
  selection+="] =";
  selection+="{\n";
  for (int i=0; i<y; i++) {

    selection+="{";
    for (int j=0; j<x-1; j++) {
      int c = get(j, i);
      selection+="matrix.Color("+red(c)+","+green(c)+","+blue(c)+"),";
    }
    int c = get(x-1, i);
    selection+="matrix.Color("+red(c)+","+green(c)+","+blue(c)+")";
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







public void fileSelected(File selection) {
  if (selection == null) {
    println("Window was closed or the user hit cancel.");

    exit();
  } else {
    //    println("User selected " + selection.getAbsolutePath());
    myImage = loadImage(selection.getAbsolutePath());
    image(myImage, 0, 0);
  }
}

public void mouseClicked() {
  myImage=null;
  selectInput("Select a file to process:", "fileSelected");
  analyse=false;
  fin=false;
}

  public void settings() {  size(600, 500); }
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "--present", "--window-color=#666666", "--stop-color=#cccccc", "analyse_image" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
