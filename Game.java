
import java.util.Random;


import javafx.animation.AnimationTimer;
import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Ellipse;
import javafx.scene.shape.Rectangle;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import javafx.scene.text.Text;
import javafx.stage.Stage;
/**
 * This is a simple hit and count game. A circle will move through the user's display window,
 * if the user clicks on it, he gets a point and then the new circle will appear within few
 * seconds at a slightly greater pace. User will only get one click per circle.
 * If the circle passes through the display window 
 * without being clicked, it will be counted as a miss. On missing the circle 5 times, 
 * the game will get over and a message will be printed on screen. User also have the option
 * of pausing the game during the game play. He can also reset the game whenever he wants. 
 * 
 * THERE IS ALSO ONE TWIST- User only gets one chance to shoot at a circle (BONUS PART)
 * 
 * @author Gaurav Shienhmar
 *
 */
public class Game extends Application{
	
	private Pane centerPane;
	BorderPane mainPane = new BorderPane();
	
	private Ellipse ball;
	private double xVelocity = 1;
	private BallMovement animation;
	private int hits = 0;
	private int misses = 0;
	private Text line;
	private Text endLine;
	private Random rand = new Random();
	private double x;
	private double y;
	private boolean pauseCheck = false;
	private boolean clickAllowed = true;
	
	@Override
	public void start(Stage primaryStage) {
		
		centerPane = new Pane();
		centerPane.setPrefWidth(460);
		centerPane.setPrefHeight(600);
		
		
		Rectangle background = new Rectangle(0, 0, 460,600);
		background.setFill(Color.BLACK);
		
		
		
		ball = new Ellipse(20,120,25,25);
		ball.setFill(Color.WHITE);
		line = new Text(10,20,"Hits : " + hits + "  Misses : " + misses);
	    line.setFill(Color.WHITE);
	    endLine = new Text(42,300,"GAME OVER");
		endLine.setFont(Font.font("Forte",FontWeight.NORMAL,65));
		endLine.setFill(Color.PINK);
		endLine.setVisible(false);

	    letsBegin();
	    
	    ball.setOnMousePressed(new ClickEventHandler());
	    background.setOnMouseClicked(new BackgroundClicked());
		centerPane.getChildren().addAll(background,endLine,ball,line);
	
		
		
		Button pause = new Button("Pause");
		pause.setOnAction(new PauseEverything());
		Button reset = new Button("Reset");
		reset.setOnAction(new ResetGame());
		HBox bottom = new HBox(5,pause,reset);
		bottom.setMargin(pause, new Insets(5));
		bottom.setMargin(reset, new Insets(5));
	
		bottom.setAlignment(Pos.CENTER_RIGHT);
		
		
		mainPane.setCenter(centerPane);
		mainPane.setBottom(bottom);
		
		
		
		animation = new BallMovement();
		animation.start();
	
		
		Scene scene = new Scene(mainPane);
		primaryStage.setTitle("ClickGame");
		primaryStage.setScene(scene);
		primaryStage.show();
		
	}
	
	public static void main(String[] args) {
		launch(args);
	}
	
	private class BallMovement extends AnimationTimer{
		@Override
		public void handle(long now) {
			
			if((x - 25) + xVelocity > 460) {
				
				misses++;
				updates();
			}
			
			else {
				x+= xVelocity;
				ball.setCenterX(x);
			}
			
			if(misses == 5) {
				endLine.setVisible(true);
				pauseCheck = true;
				animation.stop();
			}
			
			
			
		}
		
	}
	
	private void updates() {
		int leftmostPoint = (int) (60 * 4 * xVelocity);
		x = -(25 + rand.nextInt(leftmostPoint));
		y = 70 + rand.nextInt(480);
		ball.setCenterX(x);
		ball.setCenterY(y);
		line.setText("Hits : " + hits + "  Misses : " + misses);
		clickAllowed = true;
	}
	
	private void letsBegin() {
		
		if(endLine.isVisible()) {
			endLine.setVisible(false);
		}
		hits = 0;
		misses = 0;
		xVelocity = 1;
		updates();
		
	}
	
	private class ResetGame implements EventHandler<ActionEvent>{
		
	
		@Override
		public void handle(ActionEvent e) {
			letsBegin();
			if(pauseCheck == true) {
				animation.start();
				pauseCheck = false;
			}
		}
	}
	
	private class PauseEverything implements EventHandler<ActionEvent>{

		@Override
		public void handle(ActionEvent e) {

         if(pauseCheck == false) {
        	 animation.stop();
        	 pauseCheck = true;
         }
         else {
        	 animation.start();
        	 pauseCheck = false;
         }
			
		}
		
	}
	private class BackgroundClicked implements EventHandler<MouseEvent>{
		@Override
		public void handle(MouseEvent e) {
			clickAllowed = false;
		}
	}
	
	private class ClickEventHandler implements EventHandler<MouseEvent>{
		@Override
		public void handle(MouseEvent e) {
			
			if(clickAllowed == true) {
            if(pauseCheck == false) {
			xVelocity += 0.6;
			hits++;
		    updates();
            }
			}
			e.consume();
			
		}
	}
	
	
	
	

}
