from django.shortcuts import render
from rest_framework.response import Response
from django.http import JsonResponse
from rest_framework.decorators import api_view
from timer.models import ESP
from rest_framework import status
from timer.serializer import TimerSerializer

# Create your views here.
@api_view(['GET'])
def time_sent(request):
    timer = ESP.objects.all()
    serializer = TimerSerializer(timer, many = True)
    return Response(serializer.data)

@api_view(['POST'])
def time_taken(request):    
    serializer = TimerSerializer(data = request.data)
    if serializer.is_valid():
        serializer.save()
        return Response(serializer.data)
    else:
        return Response(serializer.errors, status= status.HTTP_400_BAD_REQUEST)

@api_view(['GET', 'PUT', 'DELETE'])
def time(request,pk): 
    try:
        time = ESP.objects.get(pk=pk)
    except:
        return Response({'error': 'entry does not exist'}, status= status.HTTP_404_NOT_FOUND)
    if request.method == 'GET':
        serializer = TimerSerializer(time)
        return Response(serializer.data)

    if request.method == "PUT":
        serializer = TimerSerializer(time, data=request.data)
        if serializer.is_valid():
            serializer.save()
            return Response(serializer.data)
        return Response(serializer.errors, status= status.HTTP_400_BAD_REQUEST)

    if request.method == "DELETE":
        time.delete()
        return Response(status=status.HTTP_204_NO_CONTENT)