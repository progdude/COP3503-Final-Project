#include "OpenCV.h"

using namespace cv;
using namespace std;


string OpenCV::recognize(vector<User> users) {
    


    
    string fn_haar = "haarcascade_frontalface_alt.xml";
    //string fn_csv = "/Users/Archit/Downloads/DetectsAndRecognizeFaces/Python\ script/csv.ext";
    int deviceId = 0;			// here is my webcam Id.
    // These vectors hold the images and corresponding labels:
    vector<Mat> images;
    // Read in the data (fails if no valid input filename is given, but you'll get an error message):
    
    // Get the height from the first image. We'll need this
    // later in code to reshape the images to their original
    // size AND we need to reshape incoming faces to this size
    
    // Create a FaceRecognizer and train it on the given images:
    Ptr<FaceRecognizer> model = createFisherFaceRecognizer();
    model->load(TRAINEDMODEL);
    // That's it for learning the Face Recognition model. You now
    // need to create the classifier for the task of Face Detection.
    // We are going to use the haar cascade you have specified in the
    // command line arguments:
    //
    CascadeClassifier haar_cascade;
    haar_cascade.load(fn_haar);
    // Get a handle to the Video device:
    VideoCapture cap(deviceId);
    // Check if we can use this device at all:
    if(!cap.isOpened()) {
        cerr << "Capture Device ID " << deviceId << "cannot be opened." << endl;
    }
    // Holds the current frame from the Video device
    Mat frame;
    
    /////////////////////////////
    ///creat vector of users////
    ////////////////////////////
    
    vector<string> predictions;
    predictions.reserve(users.size());
    
    for(int i = 0; i < 50; i++) {
        cap >> frame;
        // Clone the current frame:
        Mat original = frame.clone();
        // Convert the current frame to grayscale:
        Mat gray;
        cvtColor(original, gray, CV_BGR2GRAY);
        // Find the faces in the frame:
        vector< Rect_<int> > faces;
        haar_cascade.detectMultiScale(gray, faces);
        // At this point you have the position of the faces in
        // faces. Now we'll get the faces, make a prediction and
        // annotate it in the video. Cool or what?
        for(int i = 0; i < faces.size(); i++) {
            // Process face by face:
            Rect face_i = faces[i];
            // Crop the face from the image. So simple with OpenCV C++:
            Mat face = gray(face_i);
            // Resizing the face is necessary for Eigenfaces and Fisherfaces. You can easily
            // verify this, by reading through the face recognition tutorial coming with OpenCV.
            // Resizing IS NOT NEEDED for Local Binary Patterns Histograms, so preparing the
            // input data really depends on the algorithm used.
            //
            // I strongly encourage you to play around with the algorithms. See which work best
            // in your scenario, LBPH should always be a contender for robust face recognition.
            //
            // Since I am showing the Fisherfaces algorithm here, I also show how to resize the
            // face you have just found:
            Mat face_resized;
            cv::resize(face, face_resized, Size(200, 200), 1.0, 1.0, INTER_CUBIC);
            // Now perform the prediction, see how easy that is:
            
            int prediction = 0;
            double confidence = 0.0;
            model->predict(face_resized,prediction,confidence);
            // And finally write all we've found out to the original image!
            // First of all draw a green rectangle around the detected face:
            rectangle(original, face_i, CV_RGB(0, 255,0), 1);
            // Create the text we will annotate the box with:
            string box_text;
            box_text = format( "Prediction = " );
            // Get stringname
            if ( prediction >= 0)
            {
                cout<<users[prediction].name<<'\n';
                cout << confidence << endl;
                predictions.push_back(users[prediction].name);
                //box_text.append( users[prediction]->name );
                
                
            }
            else {
                //box_text.append("User Unknown");
                cout << confidence << endl;
            }
            // Calculate the position for annotated text (make sure we don't
            // put illegal values in there):
            int pos_x = std::max(face_i.tl().x - 10, 0);
            int pos_y = std::max(face_i.tl().y - 10, 0);
            // And now put it into the image:
            putText(original, box_text, Point(pos_x, pos_y), FONT_HERSHEY_PLAIN, 1.0, CV_RGB(255,255,0), 2.0);
        }
        
        if (faces.size() > 1) {
            
        }
        
        // Show the result:
        imshow("face_recognizer", original);
        // And display it:
        char key = (char) waitKey(20);
        // Exit this loop on escape:
        if(key == 27)
            break;
    }
    
    //cout << "predictions:" << &predictions << endl;
    vector<int>::iterator it;
    int i = 0;
    
    
    sort( predictions.begin( ), predictions.end( ), [ ]( const string& lhs, const string& rhs )
    {
             return lhs < rhs;
    });
    
    
    
    string current = predictions.front();
    string name = "";
    int greaterCount = 0;
    int count=0;
    for(vector<string>::size_type i = 1; i != predictions.size(); i++) {
        if(current==predictions.at(i)){
            count++;
            
            if(i==predictions.size()-1){
                if(count>greaterCount){
                    greaterCount = count;
                    name = current;
                }
                current = predictions.at(i);
                
            }
        }
        else{
            if(count>greaterCount){
                greaterCount = count;
                name = current;
            }
            current = predictions.at(i);
        }
    }

    
    
    double mass = double(greaterCount)/predictions.size();
    if(mass>.6){
                return name;
    }
    User none = *new User();

    return "No User Found";
}

void OpenCV::addNewUser(string name, vector<User> users){
    
    
    
    

    
    
    VideoCapture capture;
    Mat frame;
    
    capture.open(-1);
    
    if ( !capture.isOpened() ) {
        printf("--(!)Error opening video capture\n");
    }
    
    int count = 0;
    
    string folder = name;
    string mkdirCropped = "mkdir cropped";
    string folderCreateCommand = "mkdir cropped/" + folder;
    system(mkdirCropped.c_str());
    system(folderCreateCommand.c_str());

    while (capture.read(frame) && (count < 50))
    {
        if( frame.empty() )
        {
            printf(" --(!) No captured frame -- Break!");
            break;
        }
        
        
        //-- 3. Apply the classifier to the frame
        detectNewUser(frame, count, name);
        string window_name = "Capture - Face detection";
        namedWindow(window_name, WINDOW_AUTOSIZE );
        imshow(window_name, frame);
        int c = waitKey(10);
        if( (char)c == 27 ) { break; }
    }
    
    capture.release();
    
    string path = "cropped/";
    
    vector<Mat> images;
    vector<int> nameIndex;
    vector<User>::iterator it;
    int i = 0;
    for(it = users.begin() ; it < users.end(); it++, i++) {
        // found nth element..print and break.
        for (int j = 0; j < 50; j++){
            string file = path + name + "/" + to_string(j) + ".jpg";
            Mat image = imread(file, 0);
            Mat newImage;
            
                cv::resize(image, newImage, Size(200, 200), 0, 0, INTER_LINEAR);
           
            
            
            images.push_back(newImage);
            nameIndex.push_back(i);
        }
    }
    
    
    //trains the new model
    Ptr<FaceRecognizer> model = createFisherFaceRecognizer();
    cout<<"asdasdfasdffasf"<<endl;
    model->train(images,nameIndex);
    cout<<"asdfasf"<<endl;
    model->save(TRAINEDMODEL);
    cout<<"Swagm oney"<<endl;
    
}

void OpenCV::detectNewUser(Mat &frame, int &j, string name)
{
    Mat cropped;
    std::vector<Rect> faces;
    Mat frame_gray;
    
    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );
   
    string fn_haar = "haarcascade_frontalface_alt.xml";
    
    //-- Detect faces
    CascadeClassifier haar_cascade;
    
    if( !haar_cascade.load( fn_haar ) ){
        printf("--(!)Error loading face cascade\n");
        return;
    };
   
    haar_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );
    
    if (faces.size() != 0) {
        Point topleft(faces[0].x,faces[0].y);
        Point bottomright(faces[0].x + faces[0].width,faces[0].y + faces[0].height);
        
        rectangle(frame, topleft, bottomright, Scalar(255,255,0));
        
        Mat faceROI = frame_gray(faces[0]);
        
        cropped = frame(Rect(faces[0].x,faces[0].y,faces[0].width,faces[0].height));
        
        //saves faces to folder
        string folder = name;
        imwrite("cropped/" + folder + "/" + to_string(j) + ".jpg", cropped);
        cout << "cropped/" + folder + "/" + to_string(j) + ".jpg" << endl;
        j++;
    }
        //-- In each face, detect eyes
        //-- Show what you got
}






