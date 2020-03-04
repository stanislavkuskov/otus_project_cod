<h2> COD - camera obstacle Detector</h2>
<h5>Detection of obstacles to the movement of an unmanned dump truck (BelAZ 7513R) using computer vision technologies.
Otus C++ course final project.</h5>


Description:
The obstacle detection module is designed to detect obstacles in the path of the 
self-driving truck and transmit information about the detected obstacles to 
the on-board computer of the self-driving truck to make a decision on changing the route or stopping the movement.


Architecture:
The module includes the following elements:
- Detector - detects objects in the image. It works constantly, takes a frame from the Streamer element. A stub (face detector) is used.
- Streamer - receiving frames from the camera and their preliminary processing (if needed). Streamer works constantly to provide the Detector with the current frame at any time.
- Publisher - transmits detected objects. It picks up the current “detector” from the Detector and sends it to the network (zeroMQ publisher / subscriber).
- Visualizer - Renders “detects” on the frame if necessary. It works in a separate thread, picks up the “detector” and the frame on which the detection was performed from the Detector.