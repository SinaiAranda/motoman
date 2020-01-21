#!/usr/bin/env python
import rospy
from std_msgs.msg import String

import json
import paho.mqtt.client as mqtt

class Server:
    
    def on_connect(self, client, userdata, flags, rc):
        print("Connected with result code "+str(rc))

    def send_data(self):

        self.valores = {
            "motoman_robot_mh6-10": [
                {"idSensor": "19", "valor": self.running},
                {"idSensor": "20", "valor": self.servo_is_on},
                {"idSensor": "21", "valor": self.top_of_master_job},
                {"idSensor": "22", "valor": self.alarm_error_occurred},
                {"idSensor": "23", "valor": self.battery_alarm},
                {"idSensor": "24", "valor": self.remote_mode_selected},
                {"idSensor": "25", "valor": self.play_mode_selected},
                {"idSensor": "26", "valor": self.teach_mode_selected}
                ]
            }
        self.JSON = json.dumps(self.valores)
        #print self.valores 
        
        try:
            self.raspi.publish('cidesi/nl/robots/motoman_robot_mh6-10', self.JSON)
        except:
            print("No conexion")

    def __init__(self):
        self.alarm_error_occurred = "0"
        self.battery_alarm = "0"
        self.play_mode_selected = "0"
        self.remote_mode_selected = "0"
        self.running = "0"
        self.servo_is_on = "0"
        self.teach_mode_selected = "0"
        self.top_of_master_job = "0"

        self.valores = {}
        self.JSON = {}

        self.raspi = mqtt.Client()
        self.raspi.on_connect = self.on_connect
        self.raspi.connect('192.168.0.105', 1883)

    def battery_alarm_callback(self, msg):
        self.battery_alarm = msg.data
        self.send_data()

    def play_mode_selected_callback(self, msg):
        self.play_mode_selected = msg.data

    def remote_mode_selected_callback(self, msg):
        self.remote_mode_selected = msg.data

    def running_callback(self, msg):
        self.running = msg.data

    def servo_is_on_callback(self, msg):
        self.servo_is_on = msg.data

    def teach_mode_selected_callback(self, msg):
        self.teach_mode_selected = msg.data

    def top_of_master_job_callback(self, msg):
        self.top_of_master_job = msg.data
    def alarm_error_occurred_callback(self, msg):
        self.alarm_error_occurred = msg.data

    def top_of_master_job_callback(self, msg):
        self.top_of_master_job = msg.data

if __name__ == '__main__':
    rospy.init_node('motoman_robot_monitoring')

    server = Server()

    rospy.Subscriber('/alarm_error_occurred', String, server.alarm_error_occurred_callback)
    rospy.Subscriber('/battery_alarm', String, server.battery_alarm_callback)
    rospy.Subscriber('/play_mode_selected', String, server.play_mode_selected_callback)
    rospy.Subscriber('/remote_mode_selected', String, server.remote_mode_selected_callback)
    rospy.Subscriber('/running', String, server.running_callback)
    rospy.Subscriber('/servo_is_on', String, server.servo_is_on_callback)
    rospy.Subscriber('/teach_mode_selected', String, server.teach_mode_selected_callback)
    rospy.Subscriber('/top_of_master_job', String, server.top_of_master_job_callback)

    rospy.spin()
