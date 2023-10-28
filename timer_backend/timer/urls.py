
from django.contrib import admin
from django.urls import path
from timer.views import time_taken, time_sent,time

urlpatterns = [
    path('',time_sent),
    path("time/", time_taken),
    path('<int:pk>', time)
]
