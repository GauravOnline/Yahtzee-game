import java.util.Random;

import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Group;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.CheckBox;
import javafx.scene.control.RadioButton;
import javafx.scene.control.TextField;
import javafx.scene.control.ToggleGroup;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Pane;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.scene.shape.Arc;
import javafx.scene.shape.Ellipse;
import javafx.scene.shape.Line;
import javafx.scene.shape.Polygon;
import javafx.scene.shape.Rectangle;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import javafx.scene.text.Text;
import javafx.stage.Stage;
/**
 *
 *         A simple Beach class that displays a beautiful night scene of a beach.
 *         Since its the night time, the sky is dark blue with white moon.We also
 *         have a coconut tree with two coconuts on it.These all together make up our background.
 *         Our foreground item is a lighthouse. A big red lighthouse having a roof, top, window,
 *         body, middle part,railing ,etc.
 *         While running, the user gets some options and buttons.
 *         The user can decide whether they want to display stars and lighthouse or not.
 *         The user also get the control to rotate the tree object by 0, 90 180 and 270 degrees.
 *         Beside this, user gets an input text field, inserting text in which, followed by clicking of
 *         update caption button, gives the written output of that text in the beach scene. The
 *         writing style chosen according to the theme of beach is Forte.
 *         @author Gaurav Shienhmar
 */
public class Beach extends Application {
	private BorderPane mainPane = new BorderPane();
	private Pane centerPane;
	private Text display;
	private Text rotation;
	private Text caption;
	private CheckBox displayStars;
	private CheckBox displayLightHouse;
	private Group manystars;
	private Group tree;
	private Group RedLightHouse;
	
	private RadioButton zero;
	private RadioButton ninety;
	private RadioButton oneEighty;
	private RadioButton twoSeventy;
	private ToggleGroup angleOptions;
	
	private TextField insertLine;
	private Text line;
	
	private Stage stage;

	
	

	@Override
	public void start(Stage primaryStage) {
		
        stage = primaryStage;
        
		centerPane = new Pane();
		centerPane.setPrefWidth(1000);
		centerPane.setPrefHeight(650);
		
		Rectangle sky_above = new Rectangle(0, 0, 1000,450);
		sky_above.setFill(Color.DARKBLUE);
		
		Ellipse moon = new Ellipse(900,90,30,30);
		moon.setFill(Color.WHITE);
		
		manystars = new Group();
		star(100,100);
		star(300,295);
		star(500,89);
	    star(700,199);
		star(900,316);
		manystars.setVisible(false);
		

		Rectangle ground = new Rectangle(0,450,1000,300);
		ground.setFill(Color.BLANCHEDALMOND);
		
		
	    line = new Text(120,100,"");
	    line.setFont(Font.font("Forte",FontWeight.NORMAL,60));
		line.setFill(Color.WHITE);
		
		centerPane.getChildren().addAll(sky_above, moon,ground,manystars,line);
		tree();
	

	    display = new Text("Display");
	    display.setFont(Font.font("Arial",18));
	    
        displayStars = new CheckBox("Stars");
	     
	    LightHouse l1 = new LightHouse(700,250);
		displayLightHouse = new CheckBox("LightHouse");
		
	    DisplayEventHandler handler1 = new DisplayEventHandler();
		displayLightHouse.setOnAction(handler1);
		displayStars.setOnAction(handler1);
		
		
		HBox displayItems = new HBox(5,displayStars, displayLightHouse);
		displayItems.setMargin(displayLightHouse,new Insets(5,10,10,5));
		displayItems.setMargin(displayStars,new Insets(5,5,10,10));
		
	     
	    rotation = new Text("Rotation");
	    rotation.setFont(Font.font("Arial",18));
	    
	    zero = new RadioButton("0");
	    ninety = new RadioButton("90");
	 	oneEighty = new RadioButton("180");
	 	twoSeventy = new RadioButton("270");
	 	 
	 	
	 	
	 	angleOptions = new ToggleGroup();
	 	zero.setToggleGroup(angleOptions);
	 	ninety.setToggleGroup(angleOptions);
	 	oneEighty.setToggleGroup(angleOptions);
	 	twoSeventy.setToggleGroup(angleOptions);
	 	angleOptions.selectToggle(zero);	
	     
	 	
	 	RotateTree handler2 = new RotateTree();
		zero.setOnAction(handler2);
		ninety.setOnAction(handler2);
		oneEighty.setOnAction(handler2);
		twoSeventy.setOnAction(handler2);
		
		HBox angles1 = new HBox(5,zero,ninety); 
		angles1.setMargin(zero, new Insets(5,10,5,10));
		angles1.setMargin(ninety, new Insets(5,10,5,10));
		
		
	 	HBox angles2 = new HBox(5,oneEighty,twoSeventy);
	 	angles2.setMargin(oneEighty, new Insets(5,10,5,10));
		angles2.setMargin(twoSeventy, new Insets(5,10,5,10));
		
	 	
	 	VBox angles = new VBox(5,angles1, angles2);
	 	angles1.setAlignment(Pos.CENTER);
	 	angles2.setAlignment(Pos.CENTER);
	    
  
        caption = new Text(3,60,"Caption");
        caption.setFont(Font.font("Arial",18));
		
		insertLine = new TextField("");
		Button updateCaption = new Button("Update Caption");
	
		MessageDisplayer handler3 = new MessageDisplayer();
		//insertLine.setOnAction(handler3);
		updateCaption.setOnAction(handler3);
		
		VBox leftSide = new VBox(5, display,displayItems,rotation,angles,caption,insertLine,updateCaption);
	
		leftSide.setMargin(display, new Insets(10,10,5,10));
		leftSide.setAlignment(Pos.CENTER);
		leftSide.setMargin(displayItems, new Insets(5,5,20,5));
		leftSide.setMargin(rotation, new Insets(20,10,5,10));
		leftSide.setMargin(angles, new Insets(5,10,20,10));
		leftSide.setMargin(caption, new Insets(20,10,5,10));
		leftSide.setMargin(insertLine, new Insets(5,10,5,10));
		leftSide.setMargin(updateCaption, new Insets(5,10,10,10));
	
		Button close = new Button("Close");
		Closer finish = new Closer();
		close.setOnAction(finish);
		
		HBox bottom = new HBox(5,close);
		bottom.setMargin(close, new Insets(5));
	
		bottom.setAlignment(Pos.CENTER_RIGHT);
		
		
		mainPane.setPrefHeight(800);
		mainPane.setBottom(bottom);
		mainPane.setLeft(leftSide);
		mainPane.setCenter(centerPane);
		
	


		Scene scene = new Scene(mainPane);
		primaryStage.setTitle("Beach");
		primaryStage.setScene(scene);
		primaryStage.show();
	}

	public static void main(String[] args) {
		Application.launch(args);
	}
	
	private class LightHouse{
		private Arc roof;
		private Ellipse top;
		private Rectangle middle;
		private Rectangle window;
		private Line l1 ;
		private Polygon body;
		private Arc railing1;
		private Arc railing2;
		
		public LightHouse(int x, int y) {
			
			roof = new Arc(x + (30), y, (30), (15), 0 , 180);
			roof.setFill(Color.RED);
			
			top = new Ellipse(x + (30), y - (22) , (3),( 7));
			top.setFill(Color.CRIMSON);
		
			middle = new Rectangle(x, y, 60, 50);
			middle.setFill(Color.WHITE);
			
			window = new Rectangle(x + (15), y + (10), (30), (30));
			window.setStroke(Color.BLACK);
			window.setFill(Color.SKYBLUE);
			l1 = new Line(x + (30), y + (10), x + (30), y + (40));
			
			body = new Polygon(x, y +(50), x + 60, y + (50), x + 72, y + (330), x - 12, y +  (330));
			body.setFill(Color.RED);
			
			railing1 = new Arc(x + (30), y + (50),36, (5),180,180);
			railing2 = new Arc(x + 30, y + (70),36, (5),180,180);
			railing1.setStrokeWidth(5);
			railing1.setStroke(Color.BLACK);
			
			railing2.setStrokeWidth(5);
			railing2.setStroke(Color.BLACK);
			
			RedLightHouse = new Group();
			RedLightHouse.getChildren().addAll(roof,top,middle,window,l1,body,railing1,railing2);
			
			centerPane.getChildren().add(RedLightHouse);
			RedLightHouse.setVisible(false);
		}
	}
	
    private void star(int x, int y) {
   
		Polygon p1 = new Polygon(x,y,x + 5, y + 14, x, y + 11, x - 5, y + 14);
		Polygon p2 = new Polygon(x - 7, y + 6, x + 7, y + 6, x, y + 11);
		
		p1.setFill(Color.SILVER);
		p2.setFill(Color.SILVER);
		manystars.getChildren().addAll(p1,p2);

    	
    }
    
    private void tree() {
		
    	tree = new Group();
	    
	    Arc bark = new Arc(250,600,50,250,135,50);
		bark.setFill(Color.TRANSPARENT);
		bark.setStrokeWidth(16);
		bark.setStroke(Color.MAROON);
		
		Arc leaf1 = new Arc(297, 425,80,36,180,-180);
	    leaf1.setFill(Color.DARKGREEN);
	    
	    Arc leaf2 = new Arc(137, 425,80,36,180,-180);
	    leaf2.setFill(Color.DARKGREEN);
	    
	    Ellipse centre_leaf = new Ellipse(221 , 345, 30, 80);
	    centre_leaf.setFill(Color.DARKGREEN);
	
	    Ellipse coconut = new Ellipse(205, 415, 10,20);
	    coconut.setFill(Color.rgb(150,90,62));
	    
	    Ellipse coconut2 = new Ellipse(230, 415, 10,20);
	    coconut2.setFill(Color.rgb(150,90,62));
	   	
		tree.getChildren().addAll(bark,centre_leaf,leaf1,leaf2,coconut,coconut2);
		centerPane.getChildren().add(tree);
	}
    
    
    private class DisplayEventHandler implements EventHandler<ActionEvent> {
		@Override
		public void handle(ActionEvent e) {
			
			if(displayLightHouse.isSelected()) {
				RedLightHouse.setVisible(true);
			}
			
			else {
				RedLightHouse.setVisible(false);
			}
			
			if(displayStars.isSelected()) {
				manystars.setVisible(true);
			}
			
			else {
				manystars.setVisible(false);
			}
			
		}
	}
    
    private class RotateTree implements EventHandler<ActionEvent> {
		@Override
		public void handle(ActionEvent e) {
			
			if(zero.isSelected()) {
				tree.setRotate(0);
			}
			
			if(ninety.isSelected()) {
				tree.setRotate(90);
			}
			
			if(oneEighty.isSelected()) {
				tree.setRotate(180);
			}
			
			if(twoSeventy.isSelected()) {
				tree.setRotate(270);
			}
		
		}
	}
    
    private class MessageDisplayer implements EventHandler<ActionEvent> {
		@Override
		public void handle(ActionEvent e) {
			
			line.setText(insertLine.getText());
			
		}
		
	}
    
    private class Closer implements EventHandler<ActionEvent> {
		@Override
		public void handle(ActionEvent e) {
			
			stage.close();
			
		}
	}
	
   }
	

	


