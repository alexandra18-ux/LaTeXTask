class tooltip; 
struct WINDOW : public AudioManager, public RenderManager, public TransferManager {
	struct Interactable {
		static Clock shaderClocks;	
		static vector<Interactable*> INTERACTABLES; 
		Shader outlineShader; 		
		bool openned = false, hovered = false;
		Vector2f sizes; 	
		Interactable(Vector2f scale = Vector2f(1.f, 3.f));
		~Interactable();
		virtual bool isHover(const Vector2f& pos); 
		virtual void onHover();			    
		virtual void Open();   			    
		virtual void Close();  			    
		virtual void Rotate(); 			     
	};

	enum Scene {						     
		BackgroundPlan,
		MainPlan,
		InjectedLayer,
		PortLayer,
		FirstPlan,
		InteractableLayer,
		DraggingLayer,
		None,
	};

private:
	struct CURSOR { 				
		Vector2f pos;
		Interactable* interactable;
		float scroll = 0;
		bool lmb = false, rmb = false, holding = false;
		void update();			

		bool Interact(const bool& test);
			
	};

	struct Settings {		
		bool isVolume = true;
		bool isFPSlimit = true;
		bool UIscalingAllowed = true;
		bool isVsync = false;
		int Resolution = 0;
		int Language = 1;	
		int volume = 100;
		int UIScale = 80;
		int fps = 120;	
	};

	static RenderWindow window;
	static View camera, renderCamera;
	CURSOR mouse;
	Clock deltaTime;		
	vector<shared_ptr<PrimeTexture>> _TEXTURES; 
	KeyBindHandler Keyboard;	

	TextPack titles;		

	const String Settings_path = "SETTINGS.txt"; 

	Vector2f cameraSize{ 2560,1440 }, cameraCenter{ 2560.f / 2.f, 1440.f / 2.f };

	vector<Shader*> postShaders; 			

public:
	string currentState = "menu";	
	tooltip* ttip; 
	Settings SETTINGS;
	WINDOW();
	void slideView(Vector2f center, Vector2f size); 
	void resetCamera(Vector2f size = Vector2f(2560.f, 1440.f), Vector2f center = 			Vector2f(2560.f / 2.f, 1440.f / 2.f));  

	void deleteCameraScrolling();    
	void applyShader(Shader& shader); 
	void loadResources(); 		 
	void update(); 			 
	void SetDefaults(); 		  
	void OffLMB();			 
	void Close();			
	void resize(RESOLUTIONS newSize); 
	void Draw(Drawable* obj, Scene sc = Scene::MainPlan, const RenderStates& states 		= RenderStates::Default);  
	void DeclareBind(Keyboard::Key bind, function<void()> when_pressed, bool repeat 		= false, function<void()> when_unpressed = NULL); 
	void applyPostProcessing(vector<Shader*>& shaders);
	void updateLanguage(); 		 
	bool Interact(bool test = false); 
	void RotateInteractable();	 
	int getScroll();			
	bool isLMB();
	bool isRMB();
	bool isLMBhold();
	bool isOpen();
	shared_ptr<PrimeTexture> getTexture(String id); 
	const View& getView(); 				  
	const Vector2u& Size();
	const Vector2u& renderSize();
	const Vector2f& getMousePos();	
	const Vector2f& getCenter();
	const Vector2f& getLeftTop();	
	const Vector2f& getRightBot();	
	const VideoMode& getResolution();
	string getLanguage();
	String getText(const string& key);		  
	String getTooltip(const string& key);		

};