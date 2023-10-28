from django.db import models

# Create your models here.
class ESP(models.Model):
    timer = models.IntegerField()
    creation_time = models.DateTimeField(auto_now_add=True)
    updated_time = models.DateTimeField(auto_now=True)

    def __str__(self):
        return self.timer

