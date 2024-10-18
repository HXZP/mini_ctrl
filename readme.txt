cubemx生成代码后
1、更换Middlewares\Third_Party\FreeRTOS\Source\portable\RVDS中的ARM_CM3为副本
2、sd卡相关：Middlewares\Third_Party\FatFs\src\option中syscall.c更改
int ff_cre_syncobj (	/* TRUE:Function succeeded, FALSE:Could not create due to any error */
	BYTE vol,			/* Corresponding logical drive being processed */
	_SYNC_t *sobj		/* Pointer to return the created sync object */
)
{
  int ret;
  
  osSemaphoreDef(SEM);
  *sobj = osSemaphoreNew(1,1,osSemaphore(SEM));
  ret = (*sobj != NULL);
  
  return ret;
}

int ff_req_grant (	/* TRUE:Got a grant to access the volume, FALSE:Could not get a grant */
	_SYNC_t sobj	/* Sync object to wait */
)
{
  int ret = 0;
  
  if(osSemaphoreAcquire(sobj, _FS_TIMEOUT) == osOK)
  {
    ret = 1;
  }
  
  return ret;
}
